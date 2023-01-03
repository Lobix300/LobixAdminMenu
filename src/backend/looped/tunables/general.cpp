#include "backend/looped/looped.hpp"
#include "script_global.hpp"


namespace big
{
	//int og_value = *script_global(1653913).at(1156).as<int*>();;
	void looped::tunables_no_idle_kick()
	{
		/*if (&g.tunables.no_idle_kick && (!script_global(262145).at(1156).as<int*>() || !script_global(262145).at(1172).as<int*>()))
		{
			*script_global(1653913).at(1156).as<int*>() = 0;
			*script_global(1653913).at(1172).as<int*>() = 0;
		}
		else if (!&g.tunables.no_idle_kick && (script_global(262145).at(1156).as<int*>() || script_global(262145).at(1172).as<int*>()))
		{
			*script_global(1653913).at(1156).as<int*>() = og_value;
			*script_global(1653913).at(1172).as<int*>() = og_value;
		}*/
	}

	void looped::tunables_snow()
	{
		/*if (&g.tunables.enable_snow) //&& !script_global(262145).at(4752).as<int*>())
		{
			*script_global(262145).at(4752).as<int*>() = 1;
			*script_global(262145).at(9393).as<int*>() = 0;
		}
		else if (!&g.tunables.enable_snow) //&& script_global(262145).at(4752).as<int*>())
		{
			*script_global(262145).at(4752).as<int*>() = 0;
			*script_global(262145).at(9393).as<int*>() = 1;
		}*/
	}
}