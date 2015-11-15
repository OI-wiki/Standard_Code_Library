SPATH='.'
SS='python cpplint.py'
FILELIST(){
for filename in $(ls $SPATH)
do
	SPATH=`pwd`
	if [ -f $filename ];then
		# exec 'cpplint' $filename
		SS=$SS' '$SPATH'/'$filename
	elif [ -d $filename ];then
		#echo Directory： $filename
		cd $filename
		SPATH=`pwd`
		# echo $SPATH
		FILELIST
		cd ..
	else
		echo "$SPATH/$filename is not a common file."
	fi
done
}
cd $SPATH
FILELIST
echo $SS
# echo "Done."
