#ifndef __GHistManager_h__
#define __GHistManager_h__


#include <iostream>

#include <TH1.h>
#include <TObjArray.h>
#include <TDirectory.h>



class   GHistLinked;

class   GHistManager
{
private:
    TObjArray   histList;

    void        AddHistogramToList(GHistLinked* hist);
    virtual     TDirectory* GetOutputDirectory() = 0;
    void        RemoveHistogramFromList(GHistLinked* hist);

protected:

public:
    GHistManager();
    virtual ~GHistManager();

    void    ClearLinkedHistograms();
    void    WriteLinkedHistograms(TDirectory* dir);

    friend  class   GHistLinked;
};





class   GHistLinked : public TH1D
{
private:
    Bool_t  linked;
    TString dir;

    static  TDirectory* GetCreateDirectory(TDirectory* dir, const TString& dirName);

protected:
            TDirectory* GetOutputDirectory();

public:
    GHistLinked(const char* name, const char* title, Int_t nbinsx, Double_t xlow, Double_t xup, Bool_t linkHistogram = kTRUE, const char* dirName = "");
    GHistLinked(const GHistLinked& obj, Bool_t linkHistogram);
    GHistLinked(const GHistLinked& obj);
    virtual ~GHistLinked();

            void        AddOutputDirectory(const TString& directoryName);
            void        AddOutputDirectory(const char* directoryName)       {AddOutputDirectory(TString(directoryName));}
    const   TString&    GetOutputDirectoryName() const                      {return dir;}
            void        SetOutputDirectory(const TString& directoryName)    {dir = directoryName;}
            void        SetOutputDirectory(const char* directoryName)       {SetOutputDirectory(TString(directoryName));}
    virtual Int_t       Write(const char* name = 0, Int_t option = 0, Int_t bufsize = 0);
};


#endif
