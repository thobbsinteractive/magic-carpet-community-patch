#include "port_sdl_vga_mouse.h"
#include "port_sdl_joystick.h"

#include <cstdint>

#include "../engine/sub_main_mouse.h"
#include "../engine/read_config.h"

SDL_Joystick* m_gameController = NULL;

#define              JOY_MIN_X  0
#define              JOY_MIN_Y  0
#define            JOY_NAV_INC  4

#define       GP_FLIGHT_UPDATE  0x1
#define          GP_NAV_UPDATE  0x2
#define          GP_MOV_UPDATE  0x4

// to be modified once fully customized 
// keyboard control is implemented
#define          GP_KEY_EMU_UP  0x5252
#define        GP_KEY_EMU_DOWN  0x5151
#define       GP_KEY_EMU_RIGHT  0x4f4f
#define        GP_KEY_EMU_LEFT  0x5050

struct pointer_sys {
	int16_t x;
	int16_t y;
};
typedef struct pointer_sys pointer_sys_t;

struct vec1d {
	int16_t x;
	uint8_t x_conf;
};
typedef struct vec1d vec1d_t;

struct vec2d {
	int16_t x;
	int16_t y;
	uint8_t x_conf;
	uint8_t y_conf;
};
typedef struct vec2d vec2d_t;

gamepad_state_t gps = {};

/// \brief initialization of the SDL joystick subsystem
void gamepad_sdl_init(void)
{
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0) {
		Logger->error("SDL joystick could not be initialized! SDL_Error: {}", SDL_GetError());
	} else {
		m_gameController = SDL_JoystickOpen(0);
		if( m_gameController == NULL ) {
			Logger->debug("joystick/gamepad not detected. SDL Error: {}", SDL_GetError() );
		} else {
			if (SDL_JoystickEventState(SDL_ENABLE) != 1) {
				Logger->error("unable to initialize joystick/gamepad events. SDL Error: {}", SDL_GetError() );
			} else {
				// as a test, consider the joystick initialized only after the first axis change event is caught
				// due to the fact that after a cold-boot the joystick could send large random axis values without having been moved once
				gps.initialized = 1;
			}
		}
	}
}

/// \brief cleanup of the SDL joystick subsystem
void gamepad_sdl_close(void)
{
	SDL_JoystickClose(m_gameController);
	m_gameController = NULL;
}

/// \brief initialize gamepad maximal coordinate values, default operating mode, etc
/// \param gameResWidth maximum x value
/// \param gameResHeight maximum y value
void gamepad_init(const int gameResWidth, const int gameResHeight)
{
	gps.max_x = gameResWidth;
	gps.max_y = gameResHeight;
	joystick_set_env(gps.max_x >> 1, gps.max_y >> 1);
	set_scene(SCENE_PREAMBLE_MENU);
}

/// \brief flight support via conversion from stick coordinates to pointer coordinates
uint16_t gamepad_axis_flight_conv(const vec2d_t *stick, pointer_sys_t *point)
{
	uint16_t ret = 0;
	int16_t axis_yaw = stick->x;
	int16_t axis_pitch = stick->y;

	if ((axis_yaw < gpc.axis_dead_zone) && (axis_yaw > -gpc.axis_dead_zone)) {
		point->x = gps.rest_x;
	} else {
		// use two different linear interpolation equations since the
		// resting coordinate is not always the center of the display
		if (axis_yaw > 0) {
			point->x = (((gps.max_x - gps.rest_x) * axis_yaw) >> 15) + gps.rest_x;
		} else {
			point->x = ((gps.rest_x * axis_yaw) >> 15) + gps.rest_x;
		}
		ret = GP_FLIGHT_UPDATE;
	}

	if ((axis_pitch < gpc.axis_dead_zone) && (axis_pitch > -gpc.axis_dead_zone)) {
		point->y = gps.rest_y;
	} else {
		// use two different linear interpolation equations since the
		// resting coordinate is not always the center of the display
		if (axis_pitch > 0) {
			point->y = (((gps.max_y - gps.rest_y) * axis_pitch) >> 15) + gps.rest_y;
		} else {
			point->y = ((gps.rest_y * axis_pitch) >> 15) + gps.rest_y;
		}
		ret = GP_FLIGHT_UPDATE;
	}

	return ret;
}

/// \brief menu navigation support via conversion from stick coordinates to pointer coordinates
uint16_t gamepad_axis_nav_conv(const vec2d_t *stick, pointer_sys_t *point)
{
	uint16_t ret = 0;
	int16_t axis_nav_ns = stick->x;
	int16_t axis_nav_ew = stick->y;

	if ((axis_nav_ns < gpc.axis_dead_zone) && (axis_nav_ns > -gpc.axis_dead_zone)) {
		// point->x remains unchanged
	} else {
		point->x += JOY_NAV_INC * (axis_nav_ns >> 13);
		ret = GP_NAV_UPDATE;
	}

	if ((axis_nav_ew < gpc.axis_dead_zone) && (axis_nav_ew > -gpc.axis_dead_zone)) {
		// point->y remains unchanged
	} else {
		point->y += JOY_NAV_INC * (axis_nav_ew >> 13);
		ret = GP_NAV_UPDATE;
	}

	return ret;
}

/// \brief menu navigation support via conversion from hat coordinates to pointer coordinates
uint16_t gamepad_hat_nav_conv(const vec1d_t *hat, pointer_sys_t *point)
{
	uint16_t ret = 0;
	int16_t inv = 1;

	// dir can be a bitwise OR of two adjacent directions
	// so don't use 'else if' or 'switch'.

	if (hat->x_conf & GAMEPAD_AXIS_INVERTED) {
		inv = -1;
	}

	if (hat->x & SDL_HAT_UP) {
		point->y += inv * JOY_NAV_INC * 2;
		ret = GP_NAV_UPDATE;
	}

	if (hat->x & SDL_HAT_DOWN) {
		point->y -= inv * JOY_NAV_INC * 2;
		ret = GP_NAV_UPDATE;
	}

	if (hat->x & SDL_HAT_RIGHT) {
		point->x += JOY_NAV_INC * 2;
		ret = GP_NAV_UPDATE;
	}

	if (hat->x & SDL_HAT_LEFT) {
		point->x -= JOY_NAV_INC * 2;
		ret = GP_NAV_UPDATE;
	}

	return ret;
}

/// \brief longitudinal and transversal movement converted to hardcoded keyboard keypresses
void gamepad_hat_mov_conv(const vec1d_t *hat)
{

	if (hat->x & SDL_HAT_UP) {
		setPress(false, GP_KEY_EMU_DOWN);
		setPress(true, GP_KEY_EMU_UP);
	}

	if (hat->x & SDL_HAT_DOWN) {
		setPress(false, GP_KEY_EMU_UP);
		setPress(true, GP_KEY_EMU_DOWN);
	}

	if (hat->x & SDL_HAT_RIGHT) {
		setPress(false, GP_KEY_EMU_LEFT);
		setPress(true, GP_KEY_EMU_RIGHT);
	}

	if (hat->x & SDL_HAT_LEFT) {
		setPress(false, GP_KEY_EMU_RIGHT);
		setPress(true, GP_KEY_EMU_LEFT);
	}

	if (hat->x == 0) {
		setPress(false, GP_KEY_EMU_UP);
		setPress(false, GP_KEY_EMU_DOWN);
		setPress(false, GP_KEY_EMU_RIGHT);
		setPress(false, GP_KEY_EMU_LEFT);
	}
}

/// \brief menu navigation support via conversion from stick coordinates to pointer coordinates
void gamepad_axis_mov_conv(const vec2d_t *stick)
{
	uint16_t ret = 0;
	int16_t axis_long_inv = 1;
	int16_t axis_long = stick->x;
	int16_t axis_trans = stick->y;

	if (stick->x_conf & GAMEPAD_AXIS_INVERTED) {
		axis_long_inv = -1;
	}

	if ((axis_long < gpc.axis_dead_zone) && (axis_long > -gpc.axis_dead_zone)) {
		// player seems to always have some inertia, so the following wont't actually stop
		// longitudinal movement
		setPress(false, GP_KEY_EMU_UP);
		setPress(false, GP_KEY_EMU_DOWN);
	} else {
		// use two different linear interpolation equations since the
		// resting coordinate is not always the center of the display
		if (axis_long * axis_long_inv > 0) {
			setPress(false, GP_KEY_EMU_DOWN);
			setPress(true, GP_KEY_EMU_UP);
		} else {
			setPress(false, GP_KEY_EMU_UP);
			setPress(true, GP_KEY_EMU_DOWN);
		}
	}

	if ((axis_trans < gpc.axis_dead_zone) && (axis_trans > -gpc.axis_dead_zone)) {
		setPress(false, GP_KEY_EMU_RIGHT);
		setPress(false, GP_KEY_EMU_LEFT);
	} else {
		// use two different linear interpolation equations since the
		// resting coordinate is not always the center of the display
		if (axis_trans > 0) {
			setPress(false, GP_KEY_EMU_LEFT);
			setPress(true, GP_KEY_EMU_RIGHT);
		} else {
			setPress(false, GP_KEY_EMU_RIGHT);
			setPress(true, GP_KEY_EMU_LEFT);
		}
	}
}

/// \brief emulate a mouse based on data provided by a gamepad or joystick
/// \param gpe  gamepad_event_t event strucure populated thru SDL_PollEvent()
void gamepad_event_mgr(gamepad_event_t *gpe)
{
	uint16_t button_state = 0;
	uint8_t flight_mode = 1; // are we doing flight or menu navigation
	uint16_t dead_zone = 0;
	uint16_t conv_state = 0;
	pointer_sys_t flight;
	pointer_sys_t nav;
	vec2d stick;
	vec1d hat;

	// decide if we are hadling flight mode or menu navigation mode
	// both in the same time gets messy very fast

	// default mode, based on scene
	if (gps.nav_mode) {
		flight_mode = 0;
	}

	// overwrite scene-based mode based on what button is pressed
	if (SDL_JoystickGetButton(m_gameController, gpc.button_spell - 1)) {
		flight_mode = 0;
	}

	if (SDL_GetModState() & KMOD_CTRL) {
		flight_mode = 0;
	}

	stick.x = gpe->axis_yaw;
	stick.y = gpe->axis_pitch;
	flight.x = gps.x;
	flight.y = gps.y;
	// flight yaw/pitch is always done via two axes
	conv_state |= gamepad_axis_flight_conv(&stick, &flight);

	// menu navigation
	nav.x = gps.x;
	nav.y = gps.y;

	if (gpc.hat_nav_conf & GAMEPAD_ITEM_ENABLED) {
		// menu navigation is done via a hat control
		hat.x = gpe->hat_nav;
		hat.x_conf = gpc.hat_nav_conf;
		conv_state |= gamepad_hat_nav_conv(&hat, &nav);
	} else if (gpc.axis_nav_ns & gpc.axis_nav_ew & GAMEPAD_ITEM_ENABLED) {
		// menu navigation is done via two axes
		stick.x = gpe->axis_nav_ns;
		stick.y = gpe->axis_nav_ew;
		conv_state |= gamepad_axis_nav_conv(&stick, &nav);
	}

	if (flight_mode) {
		gps.x = flight.x;
		gps.y = flight.y;
	} else {
		gps.x = nav.x;
		gps.y = nav.y;
	}

	if (gps.x < JOY_MIN_X) {
		gps.x = JOY_MIN_X;
	} else if (gps.x > gps.max_x) {
		gps.x = gps.max_x;
	}

	if (gps.y < JOY_MIN_Y) {
		gps.y = JOY_MIN_Y;
	} else if (gps.y > gps.max_y) {
		gps.y = gps.max_y;
	}

	// longitudinal/transversal movement 
	// (aka forward/back/strafe right/strafe left)
	if (gpc.hat_mov_conf & GAMEPAD_ITEM_ENABLED) {
		// if movement is done via a hat
		hat.x = gpe->hat_mov;
		hat.x_conf = gpc.hat_mov_conf;
		gamepad_hat_mov_conv(&hat);
	}

	if (gpc.axis_long_conf & gpc.axis_trans_conf & GAMEPAD_ITEM_ENABLED) {
		// if movement is done via two axes
		stick.x = gpe->axis_long;
		stick.x_conf = gpc.axis_long_conf;
		stick.y = gpe->axis_trans;
		gamepad_axis_mov_conv(&stick);
	}

	if (gpe->btn_pressed) {
		if (gpe->btn_pressed & (1 << gpc.button_fire_R)) {
			button_state |= 0x2;
		}
		if (gpe->btn_pressed & (1 << gpc.button_fire_L)) {
			button_state |= 0x8;
		}
		if (gpe->btn_pressed & (1 << gpc.button_spell)) {
			setPress(true, 0xe0e0);
		}
		if (gpe->btn_pressed & (1 << gpc.button_fwd)) {
			setPress(true, GP_KEY_EMU_UP);
		}
		if (gpe->btn_pressed & (1 << gpc.button_back)) {
			setPress(true, GP_KEY_EMU_DOWN);
		}
	}

	if (gpe->btn_released) {
		if (gpe->btn_released & (1 << gpc.button_fire_R)) {
			button_state |= 0x4;
		}
		if (gpe->btn_released & (1 << gpc.button_fire_L)) {
			button_state |= 0x10;
		}
		if (gpe->btn_released & (1 << gpc.button_spell)) {
			setPress(false, 0xe0e0);
		}
		if (gpe->btn_released & (1 << gpc.button_fwd)) {
			setPress(false, GP_KEY_EMU_UP);
		}
		if (gpe->btn_released & (1 << gpc.button_back)) {
			setPress(false, GP_KEY_EMU_DOWN);
		}
	}

	if (gpe->btn_pressed || gpe->btn_released) {
		Logger->trace("joy pressed {}  released {}  mouse {}", gpe->btn_pressed, gpe->btn_released, button_state);
	}

	if (button_state) {
		goto announce;
	}

	if (conv_state) {
		gps.dead_zone_announced = 0;
	} else {
		if (gps.dead_zone_announced) {
			// do NOT flood MouseEvents() on frames where the joystick is resting
			return;
		} else {
			gps.dead_zone_announced = 1;
		}
	}

announce:

	MouseEvents(button_state & 0x7f, gps.x, gps.y);

	//Logger->info("gpc.axis_dead_zone not big enough fly ({},{}) nav ({},{}) conv_state {}", ge->axis_yaw, ge->axis_pitch, ge->axis_nav_ns, ge->axis_nav_ew, conv_state);
}

/// \brief once per frame read out all axes and hats, for perfect smoothness
void gamepad_poll_data(gamepad_event_t *gpe)
{

	if (!gps.initialized) {
		return;
	}

	// make sure to poll for the axis data on every single frame
	// otherwise we get janky movement since there is no event
	// if the joystick is held still outside the rest position

	if (gpc.axis_yaw_conf & GAMEPAD_ITEM_ENABLED) {
		gpe->axis_yaw = SDL_JoystickGetAxis(m_gameController, gpc.axis_yaw);
	}

	if (gpc.axis_pitch_conf & GAMEPAD_ITEM_ENABLED)  {
		gpe->axis_pitch = SDL_JoystickGetAxis(m_gameController, gpc.axis_pitch);
	}

	if (gpc.axis_long_conf & GAMEPAD_ITEM_ENABLED) {
		gpe->axis_long = SDL_JoystickGetAxis(m_gameController, gpc.axis_long);
	}

	if (gpc.axis_trans_conf & GAMEPAD_ITEM_ENABLED) {
		gpe->axis_trans = SDL_JoystickGetAxis(m_gameController, gpc.axis_trans);
	}

	if (gpc.axis_nav_ns_conf & GAMEPAD_ITEM_ENABLED) {
		gpe->axis_nav_ns = SDL_JoystickGetAxis(m_gameController, gpc.axis_nav_ns);
	}

	if (gpc.axis_nav_ew_conf & GAMEPAD_ITEM_ENABLED) {
		gpe->axis_nav_ew = SDL_JoystickGetAxis(m_gameController, gpc.axis_nav_ew);
	}

	if (gpc.hat_nav_conf & GAMEPAD_ITEM_ENABLED) {
		gpe->hat_nav = SDL_JoystickGetHat(m_gameController, gpc.hat_nav);
	}

	if (gpc.hat_mov_conf & GAMEPAD_ITEM_ENABLED) {
		gpe->hat_mov = SDL_JoystickGetHat(m_gameController, gpc.hat_mov);
	}

	// call the event handler only once per frame not inside the SDL_PollEvent() loop
	// https://stackoverflow.com/questions/39376356/non-instantaneous-jerky-movement-using-sdl2-opengl
	gamepad_event_mgr(gpe);
}

/// \brief reconfigure gamepad maximum coverage and operating mode
void set_scene(const uint8_t scene_id)
{
	gps.scene_id = scene_id;
	switch (scene_id) {
		case SCENE_PREAMBLE_MENU:
			gps.max_x = 640;
			gps.max_y = 480;
			gps.nav_mode = 1;
			break;
		case SCENE_FLIGHT:
			gps.max_x = gameResWidth;
			gps.max_y = gameResHeight;
			gps.nav_mode = 0;
			break;
		case SCENE_FLIGHT_MENU:
			gps.max_x = gameResWidth;
			gps.max_y = gameResHeight;
			gps.nav_mode = 1;
			break;
		default:
			gps.max_x = gameResWidth;
			gps.max_y = gameResHeight;
			break;
	}
	Logger->trace("set scene {}, nav_mode {}", scene_id, gps.nav_mode);
}

/// \brief set the x,y coord of the joystick rest position
/// \param x coordinate where the mouse pointer needs to end up when the joystick is in it's rest position
/// \param y coordinate where the mouse pointer needs to end up when the joystick is in it's rest position
void joystick_set_env(const int32_t x, const int32_t y)
{
	Logger->trace("pointer rest at {},{} scene {}, window size {},{}", x, y, gps.scene_id, gps.max_x, gps.max_y);
	gps.rest_x = x;
	gps.rest_y = y;
	gps.x = x;
	gps.y = y;
}

