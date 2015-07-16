#include "PPi0Sam.h"

PPi0Sam::PPi0Sam()
{

    time 	= new GH1("time", 	"time", 	1400, -700, 700);
    time_cut 	= new GH1("time_cut", 	"time_cut", 	1400, -700, 700);

    time_2g 	= new GH1("time_2g",	"time_2g", 	1400, -700, 700);
    time_2g_cut = new GH1("time_2g_cut","time_2g_cut", 	1400, -700, 700);

    IM 		= new GH1("IM", 	"IM", 		400,   0, 400);
    IM_2g 	= new GH1("IM_2g", 	"IM_2g", 	400,   0, 400);

    MM		= new GH1("MM", 	"MM", 	 	400,   800, 1200);
    MM_2g	= new GH1("MM_2g", 	"MM_2g", 	400,   800, 1200);

    // added by me
    Energy		 = new TH1D("Energy", "Photon_Energy", 350, 100, 450);

    Theta_1              = new TH1D("Theta_1", "Theta_1", 9, 0, 180); // 9s were 18s were 7s
    Theta_0              = new TH1D("Theta_0", "Theta_0", 9, 0, 180);
    Theta_1_prompt       = new TH1D("Theta_1_prompt", "Theta_1_prompt", 9, 0, 180); // all these 9s were 18s were 7s
    Theta_1_random       = new TH1D("Theta_1_random", "Theta_1_random", 9, 0, 180);
    Theta_0_prompt       = new TH1D("Theta_0_prompt", "Theta_0_prompt", 9, 0, 180);
    Theta_0_random       = new TH1D("Theta_0_random", "Theta_0_random", 9, 0, 180);

    Eng_1              = new TH1D("Eng_1", "Eng_1", 50, 100, 450);
    Eng_0              = new TH1D("Eng_0", "Eng_0", 50, 100, 450);
    Eng_1_prompt       = new TH1D("Eng_1_prompt", "Eng_1_prompt", 50, 100, 450);
    Eng_1_random       = new TH1D("Eng_1_random", "Eng_1_random", 50, 100, 450);
    Eng_0_prompt       = new TH1D("Eng_0_prompt", "Eng_0_prompt", 50, 100, 450);
    Eng_0_random       = new TH1D("Eng_0_random", "Eng_0_random", 50, 100, 450);

    MM_pi0_n_2g_h1     = new TH1D("MM_pi0_n_2g_h1", "MM_pi0_n_2g_h1", 1500, 0, 1500);
    MM_pi0_n_2g_h0     = new TH1D("MM_pi0_n_2g_h0", "MM_pi0_n_2g_h0", 1500, 0, 1500);
    MM_prompt_pi0_n_2g_h0 = new TH1D("MM_prompt_pi0_n_2g_h0", "MM_prompt_pi0_n_2g_h0", 1500, 0, 1500);
    MM_prompt_pi0_n_2g_h1 = new TH1D("MM_prompt_pi0_n_2g_h1", "MM_prompt_pi0_n_2g_h1", 1500, 0, 1500);
    MM_random_pi0_n_2g_h0 = new TH1D("MM_random_pi0_n_2g_h0", "MM_random_pi0_n_2g_h0", 1500, 0, 1500);
    MM_random_pi0_n_2g_h1 = new TH1D("MM_random_pi0_n_2g_h1", "MM_random_pi0_n_2g_h1", 1500, 0, 1500);

    TaggerAccScal = new TH1D("TaggerAccScal","TaggerAccScal",352,0,352);
}

PPi0Sam::~PPi0Sam()
{
}

Bool_t	PPi0Sam::Init()
{
    cout << "Initialising physics analysis..." << endl;
    cout << "--------------------------------------------------" << endl << endl;

    if(!InitBackgroundCuts()) return kFALSE;
    if(!InitTargetMass()) return kFALSE;
    if(!InitTaggerChannelCuts()) return kFALSE;
    if(!InitTaggerScalers()) return kFALSE;
    cout << "--------------------------------------------------" << endl;
    return kTRUE;
}

Bool_t	PPi0Sam::Start()
{
    if(!IsGoATFile())
    {
        cout << "ERROR: Input File is not a GoAT file." << endl;
        return kFALSE;
    }
    SetAsPhysicsFile();

    TraverseValidEvents();

    return kTRUE;
}

void	PPi0Sam::ProcessEvent()
{
    if (GetTrigger() -> GetNErrors() != 0) { return; }
    // fill time diff (tagger - pi0), all pi0
    FillTime(*GetNeutralPions(),time);
    FillTimeCut(*GetNeutralPions(),time_cut);

    // fill missing mass, all pi0
    FillMissingMass(*GetNeutralPions(),MM);

    // fill invariant mass, all pi0
    FillMass(*GetNeutralPions(),IM);

    // Some neutral decays
    for (Int_t i = 0; i < GetNeutralPions()->GetNParticles(); i++)
    {
        // Fill MM for 2 photon decay
        if ((GetNeutralPions()->GetNSubParticles(i) == 2) & (GetNeutralPions()->GetNSubPhotons(i) == 2))
        {
        // fill time diff (tagger - pi0), this pi0
                FillTime(*GetNeutralPions(),i,time_2g);
                FillTimeCut(*GetNeutralPions(),i,time_2g_cut);

        // fill missing mass, this pi0
                FillMissingMass(*GetNeutralPions(),i,MM_2g);

        // fill invariant mass, this pi0
                FillMass(*GetNeutralPions(),i,IM_2g);

        // WHERE ARE THE TAGGER SCALERS IN PHYSICSPI0.DAT?
        // This is the meat and gravies, here's where we fill the theta histograms for a given energy cut and for different helicities.
                // when in doubt, cout it out time:
                if (GetTrigger() -> GetHelicity() == kTRUE) // helicity 1
                {
                    // These functions can be found in PPhysicsSam, you can change the energy cut there.
                    FillTheta(*GetNeutralPions(), i, Theta_1_prompt, Theta_1_random);
                    FillEnergy(*GetNeutralPions(), i, Eng_1_prompt, Eng_1_random);
                    FillMissingMass(*GetNeutralPions(), i, MM_prompt_pi0_n_2g_h1, MM_random_pi0_n_2g_h1);
                }
                else if(GetTrigger() -> GetHelicity() == kFALSE) // helicity 0
                {
                    FillTheta(*GetNeutralPions(), i, Theta_0_prompt, Theta_0_random);
                    FillEnergy(*GetNeutralPions(), i, Eng_0_prompt, Eng_0_random);
                    FillMissingMass(*GetNeutralPions(), i, MM_prompt_pi0_n_2g_h0, MM_random_pi0_n_2g_h0);
                }
        }
    }
}

void	PPi0Sam::ProcessScalerRead()
{
    // Fill Tagger Scalers
    FillScalers(GetTC_scaler_min(),GetTC_scaler_max(),TaggerAccScal);
}

Bool_t	PPi0Sam::Write()
{
    // Write all GH1's and TObjects defined in this class
    RandomSubtraction(Theta_1_prompt, Theta_1_random, Theta_1, 4.0/84.0); // works for now but should be moved
    RandomSubtraction(Theta_0_prompt, Theta_0_random, Theta_0, 4.0/84.0);
    RandomSubtraction(MM_prompt_pi0_n_2g_h0, MM_random_pi0_n_2g_h0, MM_pi0_n_2g_h0, 4.0/84.0);
    RandomSubtraction(MM_prompt_pi0_n_2g_h1, MM_random_pi0_n_2g_h1, MM_pi0_n_2g_h1, 4.0/84.0);
    RandomSubtraction(Eng_0_prompt, Eng_0_random, Eng_0, 4.0/84.0);
    RandomSubtraction(Eng_1_prompt, Eng_1_random, Eng_1, 4.0/84.0);
    return GTreeManager::Write();
}
