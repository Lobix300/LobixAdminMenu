#include "views/view.hpp"
#include "util/scripts.hpp"

namespace big
{
	void view::player_misc()
	{
		if (ImGui::TreeNode("Misc"))
		{
			components::player_command_button<"joinceo">(g_player_service->get_selected());
			components::player_command_button<"enterint">(g_player_service->get_selected());
			components::player_command_button<"copyoutfit">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"copymodel">(g_player_service->get_selected());
			components::player_command_button<"clearwanted">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givehealth">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"givearmor">(g_player_service->get_selected());
			ImGui::SameLine();
			components::player_command_button<"giveammo">(g_player_service->get_selected());

			ImGui::Checkbox("Off The Radar", &g_player_service->get_selected()->off_radar);
			ImGui::Checkbox("Never Wanted", &g_player_service->get_selected()->never_wanted);
			ImGui::Checkbox("Semi Invincible Mode", &g_player_service->get_selected()->semi_invinciblemode);
			components::button("Gooch Test", []
			{
				*script_global(1890140).at(244).at(1).as<Player*>() = g_player_service->get_selected()->id();
				scripts::start_launcher_script(171);
			});
			ImGui::TreePop();
		}
	}
}