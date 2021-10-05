
#include "TreeReader.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This constructor is used for the plotting.C script. The paths are adjusted in order to do the plotting on lxplus or spar. //
// Only if one wishes to produce plots in ggFVR3 on BNL machines, the paths need to be updated.                             //
// TODO: change the format to look more nice                                                                               //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
TreeReader::TreeReader(std::string region, std::string sample, std::string tree_name, bool lxplus)
{
    setSample(sample);
    setRegion(region);

    std::string filename;

    if(lxplus) 
    {
        path2a = "/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/2jet/c16a/";
        path2d = "/eos/user/c/chenj/c16d-nTupDumpSpot/2jet/";
        path2e = "/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/2jet/c16e/";
    }
    else
    {
        path2a = "/atlasgpfs01/usatlas/data/jennyz/reco_ntuples/sagar/c16a/";    
        path2d = "/atlasgpfs01/usatlas/data/jennyz/reco_ntuples/chenj/";        
        path2e = "/atlasgpfs01/usatlas/data/jennyz/reco_ntuples/sagar/c16e/"; 
    }
    
    
    if(m_sample=="data"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/data.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/data.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);
            
            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/data.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/data.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/data.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/data.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);

        }
        else{
            filename = path2a + "data.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "data.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "data.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);

        }

    }

    if(m_sample=="Zjets"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/Zjets.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/Zjets.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);
            
            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/Zjets.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/Zjets.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/Zjets.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/Zjets.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "Zjets.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "Zjets.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "Zjets.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }

    }
    if(m_sample=="diboson1"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/diboson1.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/diboson1.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/diboson1.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/diboson1.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/diboson1.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/diboson1.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "diboson1.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "diboson1.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "diboson1.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="diboson2"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/diboson2.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/diboson2.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/diboson2.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/diboson2.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/diboson2.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/diboson2.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "diboson2.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "diboson2.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "diboson2.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="WWEW"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/EW_WW_MadGraph.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/EW_WW_MadGraph.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/EW_WW_MadGraph.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/EW_WW_MadGraph.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/EW_WW_MadGraph.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/EW_WW_MadGraph.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "EW_WW_MadGraph.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "EW_WW_MadGraph.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "EW_WW_MadGraph.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="Fakes"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/Fakes.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/Fakes.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/Fakes.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/Fakes.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/Fakes.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/Fakes.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "Fakes.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "Fakes.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "Fakes.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="ggf"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/ggf.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/ggf.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/ggf.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/ggf.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/ggf.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/ggf.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "ggf.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "ggf.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "ggf.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="htt"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/htt.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/htt.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/htt.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/htt.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/htt.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/htt.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "htt.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "htt.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "htt.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);

        }
    }
    if(m_sample=="top1"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/top1.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/top1.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/top1.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/top1.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/top1.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/top1.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "top1.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "top1.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "top1.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="top2"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/top2.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/top2.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/top2.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/top2.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/top2.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/top2.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "top2.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "top2.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "top2.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="vbf"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/vbf.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/vbf.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/vbf.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/vbf.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/vbf.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/vbf.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "vbf.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "vbf.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "vbf.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="Vgamma"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/Vgamma.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/Vgamma.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/Vgamma.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/Vgamma.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/Vgamma.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/Vgamma.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "Vgamma.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "Vgamma.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "Vgamma.root";
            f_the_file_c16e_0jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }
    if(m_sample=="vh"){
        if(m_region=="ggFCR3"){
            f_the_file_c16a_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/vh.root");

            t_the_tree_c16a_0jet = (TTree*)f_the_file_c16a_0jet->Get(tree_name.data());
            Init(t_the_tree_c16a_0jet);

            f_the_file_c16a_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/vh.root");

            t_the_tree_c16a_1jet = (TTree*)f_the_file_c16a_1jet->Get(tree_name.data());
            Init(t_the_tree_c16a_1jet);

            f_the_file_c16d_0jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/vh.root");

            t_the_tree_c16d_0jet = (TTree*)f_the_file_c16d_0jet->Get(tree_name.data());
            Init(t_the_tree_c16d_0jet);

            f_the_file_c16d_1jet = new TFile("/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/vh.root");

            t_the_tree_c16d_1jet = (TTree*)f_the_file_c16d_1jet->Get(tree_name.data());
            Init(t_the_tree_c16d_1jet);

            f_the_file_c16e_0jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/vh.root");

            t_the_tree_c16e_0jet = (TTree*)f_the_file_c16e_0jet->Get(tree_name.data());
            Init(t_the_tree_c16e_0jet);

            f_the_file_c16e_1jet = new TFile("/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/vh.root");

            t_the_tree_c16e_1jet = (TTree*)f_the_file_c16e_1jet->Get(tree_name.data());
            Init(t_the_tree_c16e_1jet);
        }
        else{
            filename = path2a + "vh.root";
            f_the_file_c16a_2jet = new TFile(filename.c_str());

            t_the_tree_c16a_2jet = (TTree*)f_the_file_c16a_2jet->Get(tree_name.data());
            Init(t_the_tree_c16a_2jet);

            filename = path2d + "vh.root";
            f_the_file_c16d_2jet = new TFile(filename.c_str());

            t_the_tree_c16d_2jet = (TTree*)f_the_file_c16d_2jet->Get(tree_name.data());
            Init(t_the_tree_c16d_2jet);

            filename = path2e + "vh.root";
            f_the_file_c16e_2jet = new TFile(filename.c_str());

            t_the_tree_c16e_2jet = (TTree*)f_the_file_c16e_2jet->Get(tree_name.data());
            Init(t_the_tree_c16e_2jet);
        }
    }

}
///////////////////////////////////////////////////////////////////////////
// this constructor is used for the experimental systematics dumping    //
/////////////////////////////////////////////////////////////////////////
TreeReader::TreeReader(std::string region, std::string sample, std::string tree_name, std::string campaign)
{
    setSample(sample);
    setRegion(region);

    if(m_region=="ggFCR3"){ // for ggFCR3 we have the ntuples only on eos. If one wants to run the jobs on spar will need to update the paths.
        if(campaign=="c16a"){
            path0 = "/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16a/"; 
            path1 = "/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16a/";
        }
        if(campaign=="c16d"){
            path0 = "/eos/user/c/chenj/c16d-nTupDumpSpot/0jet/";
            path1 = "/eos/user/c/chenj/c16d-nTupDumpSpot/1jet/";
        }
        if(campaign=="c16e"){
            path0 = "/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/0jet/c16e/";
            path1 = "/eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/1jet/c16e/";
        }
    }
    else{
        if(campaign=="c16a") path2 = "/atlasgpfs01/usatlas/data/jennyz/reco_ntuples/sagar/c16a/";   // for lxplus use /eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/2jet/c16a/ 
        if(campaign=="c16d") path2 = "/atlasgpfs01/usatlas/data/jennyz/reco_ntuples/chenj/";       // for lxplus use /eos/user/c/chenj/c16d-nTupDumpSpot/2jet/ 
        if(campaign=="c16e") path2 = "/atlasgpfs01/usatlas/data/jennyz/reco_ntuples/sagar/c16e/"; // for lxplus use /eos/user/s/sagar/ATLAS/DumpednTuples_Systematics/2jet/c16e/
    }
    std::string tmp_sample_name = "";

    if(m_sample == "WWEW") tmp_sample_name = "EW_WW_MadGraph";
    else tmp_sample_name = m_sample;

        if(m_region=="ggFCR3"){
            path0 += tmp_sample_name + ".root";

            f_the_file_0jet = new TFile(path0.c_str());

            t_the_tree_0jet = (TTree*)f_the_file_0jet->Get(tree_name.data());
            Init(t_the_tree_0jet);

            path1 += tmp_sample_name + ".root";

            f_the_file_1jet = new TFile(path1.c_str());

            t_the_tree_1jet = (TTree*)f_the_file_1jet->Get(tree_name.data());
            Init(t_the_tree_1jet);
        }
        else{
            path2 += tmp_sample_name + ".root";

            f_the_file_2jet = new TFile(path2.c_str());

            t_the_tree_2jet = (TTree*)f_the_file_2jet->Get(tree_name.data());
            Init(t_the_tree_2jet);
        }
}



std::vector<TTree*> TreeReader::getTrees() 
{
  std::vector<TTree*> tree_name;

   if(m_region=="ggFCR3"){
   tree_name.push_back(t_the_tree_c16a_0jet);
   tree_name.push_back(t_the_tree_c16d_0jet);
   tree_name.push_back(t_the_tree_c16e_0jet); 
   tree_name.push_back(t_the_tree_c16a_1jet);
   tree_name.push_back(t_the_tree_c16d_1jet);
   tree_name.push_back(t_the_tree_c16e_1jet);
   }
   else{
   tree_name.push_back(t_the_tree_c16a_2jet);
   tree_name.push_back(t_the_tree_c16d_2jet);
   tree_name.push_back(t_the_tree_c16e_2jet);
   }

  return tree_name;
}

std::vector<TTree*> TreeReader::getTreesPerCampaign() 
{
  std::vector<TTree*> tree_name;

   if(m_region=="ggFCR3"){
   tree_name.push_back(t_the_tree_0jet);
   tree_name.push_back(t_the_tree_1jet);
   }
   else{
   tree_name.push_back(t_the_tree_2jet);
   }

  return tree_name;
}

