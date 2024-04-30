#include<bits/stdc++.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [FILE]... [OPTION]...\n";
        std::cerr << "Options:\n";
        std::cerr << "\t-d <delimiter>\t\tspecify a delimiter (default: whitespace)\n";
        std::cerr << "\t-o <output_file>\tspecify an output file (default: output.txt)\n";
        std::cerr << "\t-l\t\t\tformat output as LaTeX table\n";
        std::cerr << "\t-h\t\t\tshow this help message and exit\n";
        return 1;
    }

    std::string filename;
    std::string delimiter = "";
    std::string outputFilename = "output.txt";
    bool formatAsLatexTable = false;

    for (int i = 1; i < argc; ++i) {
        if(strcmp(argv[i], "-h") == 0){
            std::cerr << "Usage: " << argv[0] << " [FILE]... [OPTION]...\n";
            std::cerr << "Options:\n";
            std::cerr << "\t-d <delimiter>\t\tspecify a delimiter (default: whitespace)\n";
            std::cerr << "\t-o <output_file>\tspecify an output file (default: table.txt)\n";
            std::cerr << "\t-l\t\t\tformat output as LaTeX table\n";
            std::cerr << "\t-h\t\t\tshow this help message and exit\n";
            return 0;
        } else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc) {
            delimiter = argv[++i]; // Next argument is the delimiter
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFilename = argv[++i]; // Next argument is the output file name
        } else if (strcmp(argv[i], "-l") == 0) {
            formatAsLatexTable = true; // Format output as LaTeX table
        } else {
            filename = argv[i];
        }
    }

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error opening input file: " << filename << "\n";
        return 1;
    }

    std::string cols;
    std::getline(inputFile, cols); // Read the first line (column names); for LaTeX table formatting

    std::ofstream outputFile(outputFilename);
    outputFile.close();

    std::string line;
    std::ofstream outFile(outputFilename, std::ios::app);
    while (std::getline(inputFile, line)) {
        if (line.empty()) // Skip empty lines
            continue;

        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        if (delimiter.empty()) {
            while (iss >> token)
                tokens.push_back(token);
        } else {
            while (std::getline(iss, token, delimiter[0]))
                tokens.push_back(token);
        }

        std::string formattedLine = "";
        for (size_t i = 0; i < tokens.size(); ++i) {
            formattedLine += tokens[i];
            if (i != tokens.size() - 1)
                formattedLine += " & ";
        }
        formattedLine += " \\\\ \n";

        if (!formattedLine.empty())
            outFile << formattedLine;
    }

    inputFile.close();
    outFile.close();

    if (formatAsLatexTable) {
        int numCols = 0;
        std::stringstream ss(cols);
        std::string tok;
        std::string headerNames = "";
        while (ss >> tok){
            headerNames += (headerNames == "") ? tok : " & " + tok;
            numCols++;
        }

        std::string header = "\\hline\n\t\t" + headerNames + " \\\\\n\t\\hline";
        std::ifstream tableFile(outputFilename);
        std::ostringstream content;
        content << tableFile.rdbuf();
        std::string tabularColInit = "";
        for(int i = 0; i < numCols; i++)
            tabularColInit += (i == 0) ? "|c" : (i == numCols - 1) ? "| c|" : "| c";
        std::string tableLayout = "\\begin{table}[!h]\n    \\centering\n    \\begin{tabular}{" + tabularColInit + "}\n        " + header + "\n        " + content.str() + " \t\\hline\n    \\end{tabular}\n\\end{table}";
        std::ofstream latexFile(outputFilename);
        latexFile << tableLayout << std::endl;
        latexFile.close();

        std::cout << "LaTeX table formatting complete. Output written to: " << outputFilename << "\n";
    } else
        std::cout << "Table formatting complete. Output written to: " << outputFilename << "\n";

    return 0;
}
