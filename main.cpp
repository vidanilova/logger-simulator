/**
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
    const char* v,
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
        double vcc;
        double vbat;
        int typ;
        EmulatorConfig() 
            : kosa(0), kosayear(0), measure(0), time(0), typ(0), vcc(0.0), vbat(0.0)
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
    int &typ,
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
    struct arg_str* a_typ = arg_str0("t", "type", "<base|diff|huffman>", "open");
    struct arg_lit *a_help = arg_lit0("?", "help", "Show this help");
    struct arg_end* a_end = arg_end(20);
    

    void* argtable[] = {
        a_kosa,
        a_kosayear,
        a_t,
        a_vbat,
        a_vcc,
        a_time,
        a_measure,
        a_typ,
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
        if (a_vbat -> count)
            config -> vbat = *a_vbat -> ival;
        if (a_typ->count) {
            std::string sTyp = *a_typ->sval;
            if (sTyp == "diff")
                typ = 1;
            else if (sTyp == "huff")
                typ = 2;
            else typ = 0;
        }
        for (int i = 0; i < a_t->count; i++) {
            std::string sT = a_t->sval[i];
            size_t p = sT.find(',');
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
    std::vector<double> t0;
    int verbosity;
    int typ;
    // set measurement
    LoggerMeasurements m;
    parseCmd(&config, m.temperature, typ, verbosity, argc, argv);
    m.time = config.time;
    m.kosa = config.kosa;
    m.kosa_year = config.kosayear;
    m.measure = config.measure;
    m.time = config.time;
    m.vcc = config.vcc;
    m.vbat = config.vbat;

    if (verbosity > 2) {
        std::string ct = " Temperature, degrees C ";
        std::string ctime = " Time ";
        std::string ckosa = " Plume serial number ";
        std::string ckosayear = " Production year ";
        std::string cmeasure = " Measure # ";
        std::string cvcc = " Bus voltage, V ";
        std::string cvbat = " Battery voltage, V ";


        std::cout << ctime << m.time << endl;
        std::cout << ckosa << (int)m.kosa << endl;
        std::cout << ckosayear << (int)m.kosa_year << endl;
        std::cout << cmeasure << m.measure << endl;
        std::cout << cvcc << std::fixed << std::setprecision(1) << m.vcc << endl;
        std::cout << cvbat << std::fixed << std::setprecision(1) << m.vbat << endl;

        for (std::vector <double> ::iterator it(m.temperature.begin()); it != m.temperature.end(); it++) {
            std::cout << std::fixed << std::setprecision(4) << *it << " ";
        }
        std::cout << std::endl;
    }

    // build packet(s)
    LoggerBuilder b;
    std::vector<std::string> r;


    for (auto it(m.temperature.begin());
        it != m.temperature.end();
    it++)
    {
        t0.push_back(0.0);

    }
    switch (typ){
    case 1:
    {
        b.build(r, m, t0);
        break;
    }

    case 2:  
    {
         b.build(r, m, t0);
        break;
    }
    default: 
    {
        b.build(r, m, t0);
    }
    }
    // print packets
    for (auto& a : r)
    {
        cout << bin2hexString(a) << " " << endl;
    }
}

