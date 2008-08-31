/* (C) 2000-2008, BCI2000 Project
/* http://www.bci2000.org
/*/
//---------------------------------------------------------------------------

#pragma hdrstop

#include "TaskType.h"
#include <iostream>
using namespace std;
//----------------------------------------
Tasks::Tasks()
{
    clear();
}


//----------------------------------------
Tasks::Tasks(std::string fname)
{
    clear();
    init(fname);
}

//----------------------------------------
Tasks::~Tasks()
{
    clear();
}

/*---------------------------
parseIni
description: parses the BCI2000Certification.ini file, in which the task types are defined
input: NA
output: Tasks - an array of TaskType, which describes the task and how to analyze the data for that task
*/

//----------------------------------------
void Tasks::init(std::string fname)
{
    ifstream file;
	file.open(fname.c_str());
	if (!file.is_open())
	{
		file.close();
		//cout << "Error opening BCI2000Certification.ini. Quitting."<<endl;

        returnCode =  -1;
        return;
	}

	//setup the initial tasks
	string line;
	GlobalSource = "";
	//TaskType curTask;
	//initTaskType(curTask);

    string strTok;
    bool exportData = false;
	//go through each line of the ini and parse it
    while (getline(file, line))
    {
		if (line.size() >= 2)
			if(line[0] == '%')
            	continue; //get next line after a comment

		//setup the string stream, and tokenize the first...um...token
        strTok.clear();
        stringstream ss(line);
        ss >> strTok;
		//check that this is a valid non-empty line
		if (strTok.length() == 0)
			continue;

        //this is a global signal source, which will be set for any task that does not
        //specify one; individual tasks will overwrite this
        if (tolower(strTok) == "source")
        {
			ss >> GlobalSource;
        }
        if (tolower(strTok) == "export")
        {
            exportData = true;
        }
		//go through and check out the possible acceptable tokens, and assign the values accordingly
        else if (tolower(strTok) == "name")
        {
            //create a new task, and give it its name
            TaskType curTask;
            ss >> curTask.taskName;
            curTask.exportData = exportData;
            //go through until the END is found
            bool atEnd = false;
            while (getline(file, line) && ! atEnd)
            {
                stringstream ss2(line);
                strTok.clear();
                ss2 >> strTok;
                if (tolower(strTok) == "states")
                {
                    string stateTmp;
                    while (ss2 >> stateTmp)
                        curTask.states.push_back(stateTmp);
                }
                else if (tolower(strTok) == "parms")
                {
                    string parmTmp;
                    while (ss2 >> parmTmp)
                        curTask.parms.push_back(parmTmp);
                }
                else if (tolower(strTok) == "amp")
                {
                    curTask.amp.flag = true;
                    ss2 >> curTask.amp.ch;
                }
                else if (tolower(strTok) == "damp")
                {
                    curTask.dAmp.flag = true;
                    ss2 >> curTask.dAmp.ch;
                }
                else if (tolower(strTok) == "vid")
                {
                    curTask.vid.flag = true;
                    ss2 >> curTask.vid.ch;
                    ss2 >> curTask.vid.state;
                    ss2 >> curTask.vid.stateVal;
                }
                else if (tolower(strTok) == "aud")
                {
                    curTask.aud.flag = true;
                    ss2 >> curTask.aud.ch;
                    ss2 >> curTask.aud.state;
                    ss2 >> curTask.aud.stateVal;
                }
                else if (tolower(strTok) == "source")
                {
                    ss2 >> curTask.SignalSource;
                }
                else if (tolower(strTok) == "sigproc")
                {
                    ss2 >> curTask.SigProc;
                }
                else if (tolower(strTok) == "app")
                {
                    ss2 >> curTask.App;
                }
                else if (tolower(strTok) == "parm")
                {
					string parmTmp;
					ss2 >> parmTmp;
					curTask.addParm(parmTmp);
                    //ss2 >> curTask.parmFile;
				}
                else if (tolower(strTok) == "skip")
                {
                    curTask.skip = true;
                }
                else if (tolower(strTok) == "end")
                {
                    //the end token specifies that the current task definition is complete,
                    //so add it to the array, and start a new task
                    atEnd = true;
                    this->push_back(curTask);
                    //taskTypes.push_back(curTask);

                    //initTaskType(curTask);
                }
                else if (tolower(strTok)  == "name")
                {
                    // this is an error
                    returnCode = -2;
                    return;
                }
                else
                {
                    //cout <<"Unrecognized token: "<< strTok<<". Skipping."<<endl;
                }
            } //end while getline
        }//end if strtok = "name"

	}
	file.close();

	//go through all tasks and set the global source for any that weren't specified
	/*
    for (int i = 0; i < this->size(); i++)
    {
		if ((*this)[i].SignalSource == "" && GlobalSource != "")
            (*this)[i].SignalSource = GlobalSource;
    }  */

    //now check for duplicate task names
    for (unsigned int i = 0; i < this->size(); i++)
    {
        for (unsigned int j = i+1; j < this->size(); j++)
        {
            if (strcmpi((*this)[i].taskName.c_str(),(*this)[j].taskName.c_str()) == 0)
            {
                returnCode = -3;
                return;
            }
        }
    }
    returnCode = 0;
}
void TaskType::addParm(std::string str)
{
	parmFile.push_back(str);
	int pos = str.find_last_of("\\");
	if (pos != string::npos)
	{
		parmFileDisp.push_back(str.substr(pos+1));
	}
	else
		parmFileDisp.push_back(str);
}

//-----------------------------------
TaskType::TaskType()
{
    taskName = "";
	taskFolder = "";
	parms.clear();
	parmFile.clear();
	parmFileDisp.clear();
	states.clear();
	sampleRate = 0;
	amp.ch = -1;
	amp.state = "";
	amp.stateVal = 0;
	amp.flag = false;
    dAmp.ch = -1;
	dAmp.state = "";
	dAmp.stateVal = 0;
	dAmp.flag = false;
	vid.ch = -1;
	vid.state = "";
	vid.stateVal = 0;
	vid.flag = false;
	aud.ch = -1;
	aud.state = "";
	aud.stateVal = 0;
	aud.flag = false;
    skip = false;
    exportData = false;
}

//-----------------------------------
TaskType::~TaskType()
{
}

//---------------------------------------------------------------------------
#pragma package(smart_init)
