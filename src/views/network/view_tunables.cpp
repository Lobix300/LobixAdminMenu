#include "views/view.hpp"
#include "util/scripts.hpp"
#include "fiber_pool.hpp"

namespace big
{
	void view::tunables()
	{
		components::sub_title("General");

		ImGui::BeginGroup();

		//ImGui::Checkbox("No Idle Kick", &g.tunables.no_idle_kick);
		if (ImGui::Button("No Idle Kick"))
		{
			*script_global(1653913).at(1156).as<int*>() = -1;
			*script_global(1653913).at(1172).as<int*>() = -1;
		}
		//ImGui::Checkbox("Enable Snow", &g.tunables.enable_snow);
		if (ImGui::Button("Enable Snow"))
		{
			*script_global(262145).at(4752).as<int*>() = 1;
			*script_global(262145).at(9393).as<int*>() = 0;
		}
		if (ImGui::Button("Disable Snow"))
		{
			*script_global(262145).at(4752).as<int*>() = 0;
			*script_global(262145).at(9393).as<int*>() = 1;
		}

		ImGui::EndGroup();

		ImGui::Separator();

		components::sub_title("Unlocks");

		ImGui::BeginGroup();

		if (ImGui::Button("Unlock Clothes"))
		{
			scripts::unlock_all();
		}

		ImGui::EndGroup();
	}
}