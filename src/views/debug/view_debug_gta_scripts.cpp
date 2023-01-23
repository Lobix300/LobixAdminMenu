#include "gui/components/components.hpp"
#include "gta/script_thread.hpp"
#include "hooking.hpp"
#include "natives.hpp"
#include "view_debug.hpp"
#include "pointers.hpp"

namespace big
{
	void debug::gta_scripts()
	{
		if (ImGui::BeginTabItem("GTA Scripts")) {
			static char name[32] = "";
			components::input_text_with_hint("##global_name", "Script Name", name, sizeof(name));
			if (ImGui::Button("Start Script"))
			{
				SCRIPT::REQUEST_SCRIPT(name);
				if (SCRIPT::HAS_SCRIPT_LOADED(name)) {
					SYSTEM::START_NEW_SCRIPT(name, 16000);
					SCRIPT::SET_SCRIPT_AS_NO_LONGER_NEEDED(name);
				}
			}
			ImGui::Separator();
			static GtaThread* selected_thread{};
			if (ImGui::ListBoxHeader("##scripts", ImVec2(250, 250)))
			{
				std::map<std::string, GtaThread*> sorted_threads;
				for (auto thread : *g_pointers->m_script_threads)
					if (thread && thread->m_context.m_thread_id && thread->m_handler)
						sorted_threads[thread->m_name] = thread;
				for (auto thread : sorted_threads)
					if (ImGui::Selectable(thread.second->m_name, thread.second == selected_thread))
						selected_thread = thread.second;
				ImGui::EndListBox();
			}
			if (selected_thread)
			{
				ImGui::Separator();
				ImGui::Text("Script Pointer : 0x%d", selected_thread);
				ImGui::Text("m_name : %d", selected_thread->m_name);
				ImGui::Text("m_name_hash : %d", selected_thread->m_name_hash);
				ImGui::Text("m_stack : 0x%d", selected_thread->m_stack);
				ImGui::Text("m_exit_message : 0x%d", selected_thread->m_exit_message);
				ImGui::Text("m_handler : 0x%d", selected_thread->m_handler);
				ImGui::Text("m_thread_id : %d", selected_thread->m_context.m_thread_id);
				ImGui::Text("m_instance_id : %d", selected_thread->m_instance_id);
				ImGui::Text("m_can_be_paused : %s", (bool)selected_thread->m_can_be_paused ? "true" : "false");
				ImGui::Text("m_safe_for_network_game : %s", (bool)selected_thread->m_safe_for_network_game ? "true" : "false");
				ImGui::Text("m_is_minigame_script : %s", (bool)selected_thread->m_is_minigame_script ? "true" : "false");
				ImGui::Text("m_can_remove_blips_from_other_scripts : %s", (bool)selected_thread->m_can_remove_blips_from_other_scripts ? "true" : "false");
				if (ImGui::Button("Kill Script"))
				{
					hooks::gta_thread_kill(selected_thread);
				}
			}
		}
	}
}