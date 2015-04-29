#include "parser.h"
#include <iostream>
#include <fstream>
#include <string>

Options getOptions(string paramFile)
{
    cout << paramFile << std::endl;
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
            opt.useDT = stoi(optionValue);
        }
        else if (optionType=="useMult")
        {
            opt.useMult = stoi(optionValue);
        }
        else if (optionType=="lambda1")
        {
            opt.lambda1 = stof(optionValue);
        }
        else if (optionType=="maxLength")
        {
            opt.maxLength = stoi(optionValue);
        }
        else if (optionType=="alpha")
        {
            opt.alpha = stof(optionValue);
        }
        else if (optionType=="lambda2")
        {
            opt.lambda2 = stof(optionValue);
        }
        else if (optionType=="")
        {
            continue;
        }
        else
        {
            throw runtime_error("wrong input arguments" );
        }
    }

    return opt;
}

string getInputPath(string dataset)
{
    return "data/" + dataset + "/";
}

string getOutputPath(string filepath)
{
    unsigned found = filepath.find_last_of("/\\");
    return "result/" + filepath.substr(found+1);
}

Kernel* kernelChooser(Options opt)
{
    Kernel* kernel;

    if (opt.kernelType=="CK")
    {
        kernel = new CompositeKernel(opt);
    }
    else if (opt.kernelType=="PK")
    {
        kernel = new ProductKernel(opt);
    }
    else if (opt.kernelType=="VST")
    {
        kernel = new VectorTreeKernel(opt);
    }
    else
    {
        cout << "wrong kernel type" << endl;
        exit(0);
    }

    return kernel;
}
