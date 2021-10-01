dir=$(pwd)/sys_files
observable="costhetastar"

cd $dir
hadd merged1.root $observable\_diboson1*.root $observable\_WWEW*.root
hadd merged2.root $observable\_diboson2*.root $observable\_vh*.root
hadd merged3.root $observable\_top1*.root $observable\_vbf*.root
hadd merged4.root $observable\_top2*.root $observable\_Vgamma*.root 
hadd merged5.root $observable\_ggf*.root $observable\_htt*.root
hadd merged6.root $observable\_Zjets*.root $observable\_Fakes*.root

hadd systematics.root merged*.root
rm merged*.root
rm ../error/*
rm ../log/*
rm ../output/* 
rm -v !("systematics.root")
