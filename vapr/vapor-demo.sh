tput setaf 2
echo ""
echo "**********************"
echo "FORMATTED SOURCE CODE:"
echo "**********************"
tput setaf 6
cat examples/eqn.vapor
tput setaf 2
sleep 1
echo ""
echo "*******************************"
echo "SOURCE CODE TO SPEECH COMMANDS:"
echo "*******************************"
tput setaf 6
./vtoc examples/eqn.vapor
#tput setaf 2
#echo ""
#echo "**************"
#echo "SPEECH INPUT:"
#echo "**************"
#tput setaf 6
#aplay commands.wav
tput setaf 2
sleep 1
echo "****************************"
echo "SPEECH TO TEXT USING WIT.AI:"
echo "****************************"
tput setaf 6
cat cmd_text
tput setaf 2
sleep 1
echo ""
echo "************************"
echo "VOICE COMMAND TEXT TO VAPOR:"
echo "************************"
tput setaf 6
./ctov < cmd_text
tput setaf 2
sleep 1
echo ""
echo "***************"
echo "VAPOR CODE RUN:"
echo "***************"
tput setaf 6
./ctov < cmd_text | ./vapor
tput sgr0
