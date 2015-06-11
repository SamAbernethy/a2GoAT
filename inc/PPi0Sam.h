#ifndef __PPi0Sam_h__
#define __PPi0Sam_h__

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

#include "GTreeManager.h"
#include "PPhysicsSam.h"

class	PPi0Sam  : public PPhysicsSam
{
private:
    // numbers made by Dylan
    Int_t	bin_val;
    Int_t	bin_val_e;
    Double_t yeild_0;
    Double_t yeild_0_e;
    Double_t yeild_1;
    Double_t yeild_1_e;
    Double_t asym;
    Double_t asym_e;
    Double_t err;
    Double_t err_e;

    Double_t time_0;
    TH1* 	time_pi0;
    TH1* 	time_pi0_cuts;

    TH1* 	MM_prompt_pi0;
    TH1* 	MM_random_pi0;
    TH1* 	MM_pi0;

    TH1*	Asymmetry_Theta;
    TH1*	Asymmetry_Energy;
    TH1*	Energy;

    TH1* 	Theta_1;
    TH1*	Theta_0;
    TH1*	Theta_1_prompt;
    TH1*	Theta_1_random;
    TH1*	Theta_0_prompt;
    TH1*	Theta_0_random;

    TH1*	Eng_1;
    TH1*	Eng_0;
    TH1*	Eng_1_prompt;
    TH1*	Eng_1_random;
    TH1*	Eng_0_prompt;
    TH1*	Eng_0_random;

    TH1* 	MM_prompt_pi0_n_2g_h0;
    TH1* 	MM_random_pi0_n_2g_h0;
    TH1* 	MM_pi0_n_2g_h0;

    TH1*	MM_prompt_pi0_n_2g_h1;
    TH1*	MM_random_pi0_n_2g_h1;
    TH1*	MM_pi0_n_2g_h1;

    Int_t 	N_pi0;

    GH1*	time;
    GH1*	time_cut;
    GH1*	time_2g;
    GH1*	time_2g_cut;

    GH1*	IM;
    GH1*	IM_2g;

    GH1*	MM;
    GH1*	MM_2g;

    TH1*	TaggerAccScal;

protected:
    virtual Bool_t  Start();
    virtual void    ProcessEvent();
    virtual void	ProcessScalerRead();
    virtual Bool_t    Write();

public:
    PPi0Sam();
    virtual ~PPi0Sam();
    virtual Bool_t  Init();

};
#endif

