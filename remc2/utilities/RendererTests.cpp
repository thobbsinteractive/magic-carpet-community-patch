#include "RendererTests.h"

#include "magic_enum.hpp"

#include "../portability/port_filesystem.h"
#include "../engine/CommandLineParser.h"
#include "../engine/engine_support.h"

int renderer_tests_frame_count = 0;
bool renderer_tests_success = false;
bool renderer_tests_quit = false;

// not yet covered renderer checkpoints:
// 		{RendererTestsHitCheckpoint::HD_case_6_v392, false}, {RendererTestsHitCheckpoint::Original_case_6_v392, false},
// 		{RendererTestsHitCheckpoint::HD_case_7_v406, false}, {RendererTestsHitCheckpoint::Original_case_7_v406, false},
// 		{RendererTestsHitCheckpoint::HD_case_8_v445, false}, {RendererTestsHitCheckpoint::Original_case_8_v445, false}

std::array<RendererTestsForLevel,25> renderer_tests{
	RendererTestsForLevel{100, 0, 240, false, 0, { // level 1
		{RendererTestsHitCheckpoint::HD_BYTE_E126D_case_5_v377, false}, {RendererTestsHitCheckpoint::Original_BYTE_E126D_case_5_v377, false},
	}},
	RendererTestsForLevel{200, 320, 240, false, 0, {}}, // level 2
	RendererTestsForLevel{150, 310, 240, true, 0, { // level 3 - flat shading
 		{RendererTestsHitCheckpoint::HD_BYTE_E126D_case_7_v406, false}, {RendererTestsHitCheckpoint::Original_BYTE_E126D_case_7_v406, false},
	}},
	RendererTestsForLevel{100, 0, 480, false, 0, { // level 4 - looking up to the ceiling
		{RendererTestsHitCheckpoint::HD_BYTE_E126D_case_5_v377, false}, {RendererTestsHitCheckpoint::Original_BYTE_E126D_case_5_v377, false},
	}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
	RendererTestsForLevel{1, 0, 240, false, 0, {}},
};
bool stop_renderer_tests() {
	if (renderer_tests_frame_count >= renderer_tests[CommandLineParams.GetSetLevel()].max_frames) {
		renderer_tests_eval_findings();
		return true;
	}
	return false;
}
void renderer_tests_eval_findings() {
	renderer_tests_quit = true;

	renderer_tests_success = true;
	for (auto& [key, hit] : renderer_tests[CommandLineParams.GetSetLevel()].must_hit_checkpoints) {
		if (!hit) {
			Logger->error("Renderer test failed: {} not hit", magic_enum::enum_name(key));
			renderer_tests_success = false;
		}
	}

	if (renderer_tests[CommandLineParams.GetSetLevel()].differences > 0) {
		Logger->error("Differences between HD and Original renderer: {0}", renderer_tests[CommandLineParams.GetSetLevel()].differences);
		renderer_tests_success = false;
	}

	if (!renderer_tests_success) {
		allert_error();
	}
	else {
		Logger->info("No differences between HD and Original renderer and all checkpoints hit");
	}
}
void renderer_tests_register_hit(const RendererTestsHitCheckpoint& checkpoint) {
	renderer_tests[CommandLineParams.GetSetLevel()].must_hit_checkpoints[checkpoint] = true;
}
