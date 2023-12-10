#!/bin/bash

ko='\e[00;31m';
wipe='\e[00m';
ok='\e[01;32m';

COMMAND="$1"
PATH=..
BASE=.
TEST=$PATH/Test/fich_tests
LOG=$PATH/Test/Log
RET=

/usr/bin/rm -rf $LOG
/usr/bin/mkdir $LOG

function test_uni1 {
    RET=0
    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then
    /usr/bin/rm -rf $PATH/Test/Result_Uni1/
    /usr/bin/mkdir $PATH/Test/Result_Uni1/
	while read i
	do
 	    ../bin/scrutin -i $TEST/$i  -o $LOG/log_uni1_${i} -m uni1 > $PATH/Test/Result_Uni1/$i.txt
#        /usr/bin/cat -A $PATH/Test/ref_uni1/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Uni1/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_uni1/$i.txt $PATH/Test/Result_Uni1/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_uni1/$i.txt $PATH/Test/Result_Uni1/$i.txt)
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i"

	done <$PATH/Test/file_list_ballots.txt
    else
    echo "Not Running " $COMMAND
	RET=2
    fi

}

function test_uni2 {
    RET=0

    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then

    /usr/bin/rm -rf  $PATH/Test/Result_Uni2/
    /usr/bin/mkdir  $PATH/Test/Result_Uni2/

	while read i
	do
 	    ../bin/scrutin -i $TEST/$i  -o $LOG/log_uni2_${i} -m uni2 > $PATH/Test/Result_Uni2/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_uni2/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Uni2/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_uni2/$i.txt $PATH/Test/Result_Uni2/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_uni2/$i.txt $PATH/Test/Result_Uni2/$i.txt)
        RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <$PATH/Test/file_list_ballots.txt
    else
	RET=2
    fi

}

function test_minimaxb {
    RET=0
    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then
    /usr/bin/rm -rf $PATH/Test/Result_Cmb/
    /usr/bin/mkdir $PATH/Test/Result_Cmb/

	while read i
	do
 	    ../bin/scrutin -i $TEST/$i  -o $LOG/log_minimax_${i} -m cm > $PATH/Test/Result_Cmb/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_cm/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Cmb/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_cm/$i.txt $PATH/Test/Result_Cmb/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_cm/$i.txt $PATH/Test/Result_Cmb/$i.txt)
        RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;
	done <$PATH/Test/file_list_ballots.txt
    else
	RET=2
    fi
}

function test_minimaxd {
    RET=0
    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then
    /usr/bin/rm -rf  $PATH/Test/Result_Cmd/
    /usr/bin/mkdir  $PATH/Test/Result_Cmd/

	while read i
	do
 	    ../bin/scrutin -d $TEST/$i  -o $LOG/log_minimax_${i} -m cm > $PATH/Test/Result_Cmd/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_cm/$i.txt
#       printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Cmd/$i.txt
#       /usr/bin/dos2unix $PATH/Test/ref_cm/$i.txt $PATH/Test/Result_Cmd/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_cm/$i.txt $PATH/Test/Result_Cmd/$i.txt)
        RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;
	done <$PATH/Test/file_list_duels.txt
    else
	RET=2
    fi
}
*/
function test_schulzeb {
    RET=0

    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then

    /usr/bin/rm -rf $PATH/Test/Result_Csb/
    /usr/bin/mkdir $PATH/Test/Result_Csb/

	while read i
	do
 	    ../bin/scrutin -i $TEST/$i  -o $LOG/log_schulze_${i} -m cs > $PATH/Test/Result_Csb/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_cs/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Csb/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_cs/$i.txt $PATH/Test/Result_Csb/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_cs/$i.txt $PATH/Test/Result_Csb/$i.txt)
        RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <$PATH/Test/file_list_ballots.txt
    else
	RET=2
    fi

}

function test_schulzed {
    RET=0

    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then


    /usr/bin/rm -rf $PATH/Test/Result_Csd/
    /usr/bin/mkdir $PATH/Test/Result_Csd/

	while read i
	do
 	    ../bin/scrutin -d $TEST/$i  -o $LOG/log_schulze_${i} -m cs > $PATH/Test/Result_Csd/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_cs/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Csd/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_cs/$i.txt $PATH/Test/Result_Csd/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_cs/$i.txt $PATH/Test/Result_Csd/$i.txt)
        RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <$PATH/Test/file_list_duels.txt
    else
	RET=2
    fi

}

function test_pairesb {
    RET=0
    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then
    /usr/bin/rm -rf  $PATH/Test/Result_Cpb/
    /usr/bin/mkdir  $PATH/Test/Result_Cpb/

	while read i
	do
 	    ../bin/scrutin -i $TEST/$i  -o $LOG/log_paires_${i} -m cp > $PATH/Test/Result_Cpb/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_cp/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Cpb/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_cp/$i.txt $PATH/Test/Result_Cpb/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_cp/$i.txt $PATH/Test/Result_Cpb/$i.txt)
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;
	done <$PATH/Test/file_list_ballots.txt
    else
	RET=2
    fi
}

function test_pairesd {
    RET=0
    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then
    /usr/bin/rm -rf $PATH/Test/Result_Cpd/
    /usr/bin/mkdir $PATH/Test/Result_Cpd/

	while read i
	do
 	    ../bin/scrutin -d $TEST/$i  -o $LOG/log_paires_${i} -m cp >  $PATH/Test/Result_Cpd/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_cp/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Cpd/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_cp/$i.txt $PATH/Test/Result_Cpd/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_cp/$i.txt $PATH/Test/Result_Cpd/$i.txt)
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;
	done <$PATH/Test/file_list_duels.txt
    else
	RET=2
    fi
}

function test_jm {
    RET=0

    if [ -x $BASE/$COMMAND ]
    echo "Running " $COMMAND
    then


    /usr/bin/rm -rf  $PATH/Test/Result_Jm/
    /usr/bin/mkdir  $PATH/Test/Result_Jm/

	while read i
	do
 	    ../bin/scrutin -i $TEST/$i  -o $LOG/log_jm_${i} -m jm >  $PATH/Test/Result_Jm/${i}.txt
#	    /usr/bin/cat -A $PATH/Test/ref_jm/$i.txt
#        printf "\n"
#        /usr/bin/cat -A $PATH/Test/Result_Jm/$i.txt
#        /usr/bin/dos2unix $PATH/Test/ref_jm/$i.txt $PATH/Test/Result_Jm/$i.txt
	    DIFF=$(/usr/bin/diff -b -E $PATH/Test/ref_jm/$i.txt $PATH/Test/Result_Jm/$i.txt)
	    RET=$?
	    [ $RET -eq 0 ] && printf "\t%-12s [${ok}OK${wipe}]\n" "$i"
	    [ $RET -ne 0 ] && printf "\t%-12s [${ko}KO${wipe}]\n" "$i" && return;

	done <$PATH/Test/file_list_ballots.txt
    else
	RET=2
    fi

}

function test {
    test_$1
    [ $RET -eq 0 ] && printf "===> %-12s [${ok}OK${wipe}]\n" "$1"
    [ $RET -ne 0 ] && printf "xxx> %-12s [${ko}KO${wipe}]\n" "$1"
}

echo Executing $COMMAND in directory $PWD

test uni1;
test uni2;
test minimaxb;
test minimaxd;
test schulzeb;
test schulzed;
test pairesb;
test pairesd;
test jm;

exit 0
