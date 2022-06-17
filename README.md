# Logger simulator
 
## Section 1

_First, we install Git Bash to emulate command line work from the official website https://git-scm.com/downloads.
We select the version that suits the parameters of your PC. In my case, installed the 64-bit version._

---

1. After downloading, we install the emulator.
2. Next, be sure to check the box in order to show the program icon on the desktop.
3. Select the item for Visual Studio Code.
4. Click on all options to install.
5. We wait until the installation is completed. The installation was successful.
6. We opened a command line and entered several codes to activate the link with this PC.

Next, go to the official GitHub website and create your account (specify your email and come up with any password).
If the registration was successful, a green check mark will be displayed next to the data.

---

_Download from the official site https://cmake.org/download/.
Then scroll down a little and again select exactly the version that you need._

Download, then install step by step:
 1. Select Repair, click next.
 2. Install to the end and check the empty boxes. In my case, this program was already pre-installed.
 3. After installation, go to the command line using the "Start" tab or press "Win + R" and enter cmd.
 4. Troubleshooting.
 5. Next, we entered several commands to link the account that was registered on the official website.
 6.Then, without closing back, 
 we go into Git Bash and write the codes and our address so that the error notification does not show.

---

Installing the Visual Studio IDE. Building the project library.
Almost everything is ready, it remains only to create traffic. 
*First To do this, 
download Visual Studio from the official website https://visualstudio.microsoft.com/ or you can find any source.
*Second. Next, select the option with C++. 
*Third. Click on install and wait while the files are unpacked.
*Fourth. After installation, run the program and do the following: 
create a project, do not close the program and open the command line again and enter the following codes.
*Fifth. If everything works flawlessly, 
now let's go to our Git Bash and additionally write down 
more codes for input  after that we will return back to Virtual Studio and right-click on "Build".
*Lastly. The assembly was successful. 
*Library collected.

---

### Section 2

So, for starters, 
we download an additional program from the official website https://www.farmanager.com/download.php?l=ru. 
Far Manager is a utility that can copy your data and transfer it inside the Visual Studio drive. 
Next, select any file format that suits you according to the parameters of this PC.
After downloading, run the installation file and click on "Next".
After the full installation, 
we launch Far Manager and go to the first window and select the User folder 
(thus, we go to the internal data of our computer and its user).
Let's copy our given project using the command.

We write after the specified project "git clone https://github.com/commandus/empty-project.git" in the src folder. 
Click on "Shift + O" and check if it works without errors.
After that, we launch Visual Studio, and again click "Build" on the project (which was copied).
Let's check if everything works.

--- 

***Removing the hidden src/empty-project/.git folder is an action that removes the link to the github repository 
(after the initial project setup, it will be linked to the second new github project, not the empty template).***
To do this, go to the Visual Studio debug console and delete the first project, after deleting it will still remain.
Open it in notepad. We supplement.

---

***Create a build folder and generate a VS solution: cd src/empty-project; mkdir build; cd build; cmake ..***
1. First, we add the included files to the project: #include <string>, <vector> and using namespace std.
2. Copy the path and paste static const std::string programName = "empty-project"; 
std::string bin2hexString(const std::string& value);
3. We write device parameters like: temperature, battery heating, date, etc.

--

*Register for Live Share.*
1.We come into the Visual Studio, and we are registered on Live Share.
2. After clicking the button, you will have two ways: the first is to log in with a Windows account, 
the second is to log in with a GitHub account, 
in my case I went through the second method. Now you can share your project or work together.
3. Next, we create a class and several integers.
4. Fixed a few more settings.
5. We put a timer in the project, first we right-click on empty-project> Properties> Debugging> Command Arguments 
and write *--time 2012-03-02T04:07:34 12.0 13.1 14.2*
6. We clean up the excess and bring the project in order.
7. Fixed internal parameters and added some more device data.
8. We transfer the project file through Far Manager: 
 _git add README. md_
 _git commit -m "first commit"_
 _git push -u origin main_

The project ended up looking like this:

```/**
 * @brief empty project
 * @file main.cpp
 * Copyright (c) 2022 @ikfia.ysn.ru
 * Yu.G. Shafer Institute of Cosmophysical Research and Aeronomy of Siberian Branch of the Russian Academy of Sciences
 * MIT license
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <vector>
#include "logger-huffman/logger-builder.h"
#include "strptime.h"
#include "string.h"
#include "argtable3/argtable3.h"
#include <time.h>
#include <cstdio>
using namespace std;

const static char *dateformat0 = "%FT%T";
const static char* dateformat1 = "%Y-%m-%dT%H:%M:%S";
/*time_t time(time_t* ttime) */
/**
 * Parse NULL-terminated timstamp string
 * @return  Unix epoch time (seconds) or 2015-11-25T23:59:11
 */

static time_t string2time(
	const char *v,
	bool isLocaltime
)
{
	struct tm tmd;
	memset(&tmd, 0, sizeof(struct tm));

	time_t r=0;
	if ((strptime(v, dateformat0, &tmd) == NULL)
		&& (strptime(v, dateformat1, &tmd) == NULL)) 
	{
        r = strtol(v, NULL, 0);
	}
	return r;
}

static time_t string2time2(
	const char *v,
	bool isLocaltime
)
{
	struct tm tmd;
	memset(&tmd, 0, sizeof(struct tm));
}


class EmulatorConfig {
    public:
        int kosa; 
        int kosayear;
        int measure;
        time_t time;
        int vcc;
        int vbat;
        EmulatorConfig() 
            : kosa(0), kosayear(0), measure(0), time(0), vcc(0.0), vbat(0.0)
        {
            
        };
};

static const std::string programName = "empty-project";
std::string bin2hexString (const std::string& value);
/**
 * Parse command line
 * Return 0- success
 *        1- show help and exit, or command syntax error
 *        2- output file does not exists or can not open to write
 **/
static int parseCmd(
    EmulatorConfig *config,
    std::vector<double> &t,
    int &verbosity,
    int argc, 
    char *argv[])
{
    struct arg_int* a_kosa = arg_int1("k", "kosa", "<number>", "plume serial number"); 
    struct arg_int* a_kosayear = arg_int1("y", "kosa year", "<date of origin: 08.06.2022>", "year");

    struct arg_str* a_t = arg_strn(nullptr, nullptr, "<temperature>", 1, 28, "Temperature, degrees C");
    struct arg_int* a_vbat = arg_int0("b", "vbat", "<voltage:high>", "Battery voltage, V");
    struct arg_int* a_vcc = arg_int0("c", "vcc", "<voltage>", "Bus voltage, V");
    struct arg_str* a_time = arg_str0("t", "time", "<YYYY-MM-DDThh:mm:ss>", "measurement time");
    struct arg_int* a_measure = arg_int0("m", "measure", "width", "thickness");
    struct arg_lit *a_verbosity = arg_litn("v", "verbose", 0, 3, "Set verbosity level");
    struct arg_lit *a_help = arg_lit0("?", "help", "Show this help");
    struct arg_end *a_end = arg_end(20);

    void* argtable[] = {
        a_kosa,
        a_kosayear,
        a_t,
        a_vbat,
        a_vcc,
        a_time,
        a_measure,
        a_verbosity, a_help, a_end
    };

    // verify the argtable[] entries were allocated successfully
    if (arg_nullcheck(argtable) != 0) {
        arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
        return 1;
    }
    // Parse the command line as defined by argtable[]
    int nerrors = arg_parse(argc, argv, argtable);

    if ((nerrors == 0) && (a_help->count == 0)) {
        if (a_kosa->count)
            config->kosa = *a_kosa-> ival;
        if (a_kosayear->count)
            config->kosayear = *a_kosayear-> ival;
        if (a_measure->count)
            config->measure = *a_measure->ival;
        verbosity =  a_verbosity -> count;
        // parse date time
        // config->time = *a_time->sval;
        if (a_time->count)
            config->time = string2time(*a_time->sval, true);
        if (a_vcc->count)
            config->vcc = *a_vcc->ival;
        if (a_vbat->count)
            config->vbat = *a_vbat->ival;
        for (int i = 0; i < a_t->count; i++) {
            std::string sT = a_t->sval[i];
            size_t p = sT.find('.');
            if (p != std::string::npos)
                sT[p] = '.';
            double d = strtod(sT.c_str(), nullptr);
            t.push_back(d);
        }
    }

    // special case: '--help' takes precedence over error reporting
    if ((a_help->count) || nerrors) {
        if (nerrors)
            arg_print_errors(stderr, a_end, programName.c_str());
        std::cerr << "Usage: " << programName << std::endl;
        arg_print_syntax(stderr, argtable, "\n");
        std::cerr
            << "Empty project" << std::endl
            << "  empty-project" << std::endl;

        arg_print_glossary(stderr, argtable, "  %-25s %s\n");
        arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));

        return -1;
    }

    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
    return 0;
}

int main(int argc, char** argv)

{
    // read command line args
    EmulatorConfig config;
    std::vector<double> t;
    int verbosity;
    parseCmd(&config, t, verbosity, argc, argv);
    // set measurement
    LoggerMeasurements m;
    m.time = config.time;
    m.kosa = config.kosa;
    m.kosa_year = config.kosayear;
    m.measure = config.measure;
    m.time = config.time;
    m.vcc = config.vcc;
    m.vbat = config.vbat;
    
    if (verbosity > 2) {
        std::string ct = " temperature, degrees C ";
        std::string ctime = " time ";
        std::string ckosa = " plume serial number ";            
        std::string ckosayear = " production year ";   
        std::string cmeasure = " measure # ";
        std::string cvcc = " Bus voltage, V ";                                          
        std::string cvbat = " Battery voltage, V ";
        
        std::cout << ctime << m.time << endl;
        std::cout << ckosa <<(int) m.kosa << endl;
        std::cout << ckosayear << (int) m.kosa_year << endl;
        std::cout << cmeasure << m.measure << endl;
        std::cout << cvcc << std::fixed << std::setprecision(1) << m.vcc << endl;
        std::cout << cvbat << std::fixed << std::setprecision(1) << m.vbat << endl;

        for (std::vector<double>::iterator it(t.begin()); it != t.end(); it++) {
            std::cout << std::fixed << std::setprecision(4) << *it << " ";
        }
        std::cout << std::endl;
    }
   
    
    // build packet(s)
    LoggerBuilder b;
    std::vector<std::string> r;
    b.build(r, m, t);

    // print packets
    for (auto& a : r)
    {
        cout << bin2hexString(a) << " " << endl;
    }
}```