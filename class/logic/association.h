#include "card_test.h"
#include "minion_test.h"

using namespace std;

Card* ntoc(int n)
{
	Card* tmp;
	switch (n)
	{
	case 1: tmp = new Wisp_card; break;
	case 2:	tmp = new Murloc_raider_card; break;
	case 3: tmp = new Bloodfen_raptor_card; break;
	case 4: tmp = new River_crocolisk_card; break;
	case 5: tmp = new Magma_Rager_card; break;
	case 6: tmp = new Chiliwind_yeti_card; break;
	case 7: tmp = new Oasis_snapjaw_card; break;
	case 8: tmp = new Boulderfist_ogre_card; break;
	case 9: tmp = new Core_hound_card; break;
	case 10: tmp = new War_golem_card; break;
	}
	return tmp;
}