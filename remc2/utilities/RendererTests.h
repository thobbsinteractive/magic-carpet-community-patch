#pragma once

#include <array>
#include <map>
#include <string>

// renderer regressions tests data for comparing HD and original renderer
enum class RendererTestsHitCheckpoint {
	HD_case_4_v339, Original_case_4_v339,
	HD_case_5_v377, Original_case_5_v377,
	HD_case_6_v392, Original_case_6_v392,
	HD_case_7_v406, Original_case_7_v406,
	HD_case_8_v445, Original_case_8_v445,
};

extern int renderer_tests_frame_count;
extern bool renderer_tests_success;
extern bool renderer_tests_quit;
constexpr int renderer_tests_frame_count_max = 100;
typedef std::pair<RendererTestsHitCheckpoint, bool> RendererTestsHitCheckpointPair;
typedef std::map<RendererTestsHitCheckpoint, bool> RendererTestsHitCheckpointMap;
typedef struct {
	int max_frames;
	int set_mouse_x;
	int set_mouse_y;
	int differences;
	std::map<RendererTestsHitCheckpoint, bool> must_hit_checkpoints;
} RendererTestsForLevel;
extern std::array<RendererTestsForLevel,25> renderer_tests;
bool stop_renderer_tests();
void renderer_tests_eval_findings();
void renderer_tests_register_hit(const RendererTestsHitCheckpoint& checkpoint);
