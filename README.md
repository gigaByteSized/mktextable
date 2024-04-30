# mktextable

This is a command line tool that formats a dataframe (tab/whitespace separated, csv, etc...) to a LaTeX table format.

## Setup

```
git clone https://github.com/gigaByteSized/mktextable.git
g++ mktextable.cpp -o mktextable
./mktextable
```

## Overview
Sample txt file named `input.txt`
```
a   b   c   d
1   2   3   4
5   6   7   8
```

```
mktextable input.txt
```

outputs
```
1 & 2 & 3 & 4 \\ 
5 & 6 & 7 & 8 \\ 
```

```
mktextable input.txt -l
```

outputs
```
\begin{table}[!h]
    \centering
    \begin{tabular}{|c| c| c| c|}
        \hline
                a & b & c & d \\
        \hline
        1 & 2 & 3 & 4 \\
5 & 6 & 7 & 8 \\
        \hline
    \end{tabular}
\end{table}
```

Note: -l flag ingests the default output file created by mktextable. 


### TODO:
Tokenize content per line and edit formatting for -l flag.