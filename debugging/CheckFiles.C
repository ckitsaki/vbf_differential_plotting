void checkFiles()
{
	const char* inDir = "../sys_files";

	char* dir = gSystem->ExpandPathName(inDir);
	void* dirp = gSystem->OpenDirectory(dir);


	const char* entry;
	Int_t n = 0;
	TString str;
	
	
	while( (entry = (char*)gSystem->GetDirEntry(dirp) ) )
	{
		str = entry;
		if(str.EndsWith(".root")) {
			TFile myfile(gSystem->ConcatFileName(dir,entry));
			if(myfile.IsZombie()) std::cout<<gSystem->ConcatFileName(dir,entry)<<" a zombie file found\n";
			if(myfile.GetNkeys()==0) std::cout<<gSystem->ConcatFileName(dir,entry)<<" ==> resubmit this job please\n";
			myfile.Close(); n++;	
		}
	}

	std::cout<<"Checks ended\n"; 	
}  
