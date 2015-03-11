#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>

string PATH = "/home/kim/xresearch/";

// Index where the flag value changes

Options getOptions(string paramFile)
{
    std::ifstream infile(paramFile);
    Options opt;

    while (infile.good())
    {
        std::string line;
        getline(infile, line);
        std::stringstream linestream(line);

        string optionType;
        string optionValue;
        getline(linestream, optionType, ':');
        getline(linestream, optionValue, ':');

        if (optionType=="dataset")
        {
            opt.dataset = optionValue;
        }
        else if (optionType=="kernelType")
        {
            opt.kernelType = optionValue;
        }
        else if (optionType=="useDT")
        {
            opt.useDT = atoi(optionValue.c_str());
        }
        else if (optionType=="dataSize")
        {
            opt.dataSize = atoi(optionValue.c_str());
        }
        else if (optionType=="lambda")
        {
            opt.lambda = atof(optionValue.c_str());
        }
        else if (optionType=="maxLength")
        {
            opt.maxLength = atoi(optionValue.c_str());
        }
        else if (optionType=="useSent")
        {
            opt.useSent = atoi(optionValue.c_str());
        }
        else if (optionType=="useSWN")
        {
            opt.useSWN = atoi(optionValue.c_str());
        }
        else if (optionType=="sigma1")
        {
            opt.sigma1 = atof(optionValue.c_str());
        }
        else if (optionType=="sigma2")
        {
            opt.sigma2 = atof(optionValue.c_str());
        }
        else if (optionType=="")
        {
            continue;
        }
        else
        {
            cout << "wrong input arguments" << endl;
            exit(0);
        }
    }

    return opt;
}

string getInputPath(string dataset)
{
    return PATH + "data/" + dataset + "/";
}

string getOutputPath(string filepath)
{
    unsigned found = filepath.find_last_of("/\\");
    return PATH + "result/" + filepath.substr(found+1) + ".csv";
}

vtKernel* kernelChooser(Options opt)
{
    vtKernel* kernel;

    if (opt.kernelType=="bst")
    {
        kernel = new bstKernel(opt);
    }
    else if (opt.kernelType=="vst")
    {
        kernel = new vstKernel(opt);
    }
    else if (opt.kernelType=="str")
    {
        kernel = new strKernel(opt);
    }
    else if (opt.kernelType=="pst")
    {
        kernel = new pstKernel(opt);
    }
    else if (opt.kernelType=="rw")
    {
        kernel = new rwKernel(opt);
    }
    else
    {
        cout << "wrong kernel type" << endl;
        exit(0);
    }

    return kernel;
}


