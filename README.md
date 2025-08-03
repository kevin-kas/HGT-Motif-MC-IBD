# Subgraph Motif Analysis Tool (bf) - Usage Guide

## Overview
The `bf` tool identifies subgraph motifs of a specified size (K) from network data and counts their occurrences. Output includes motif classification information (taxonID), structure, and occurrence count.


## Command Format
```bash
./bf <K-value> <taxon_file_path> < <data_file_path>
```


## Parameter Explanation
| Parameter Position       | Description                                  | Example Value                                  |
|--------------------------|----------------------------------------------|------------------------------------------------|
| First parameter          | Size of the subgraph (K, positive integer)   | `3` (analyzes 3-node subgraphs)                |
| Second parameter         | Path to the taxon file (CSV)                  | `TaxonID.csv` (taxon file in current directory) |
| Input redirection part   | Path to the network data file (CSV)           | `data/C3001/C3001C1.species_species.100.csv`   |


## Example Command
Assume:
- Analyzing **3-node subgraphs** (K=3)
- Taxon file: `TaxonID.csv` (in current directory)
- Data file: `data/C3001/C3001C1.species_species.100.csv`

Run the command as an example:
```bash
./bf 3 IBD_TaxonID.csv < data/C3001/C3001C1.species_species.100.csv
```


## Input File Requirements
1. **Taxon File**:  
   CSV format containing mappings between node reference IDs and taxonIDs (format must comply with parsing logic in the `read_taxon` function of the source code).

2. **Data File**:  
   CSV format where the first line lists node identifiers, and subsequent lines describe connectivity between the corresponding node and others (used to build adjacency matrix; parsing logic in the `read_data` function of the source code).


## Output Description
Each line represents a subgraph motif with the format:
```
K  taxonID1  taxonID2  ...  taxonIDK  e11 e12 ... eKK  count
```
- `taxonID1...taxonIDK`: Taxon IDs of nodes in the motif
- `e11...eKK`: Adjacency matrix of the motif (1 = edge exists, 0 = no edge)
- Last value: Number of times the motif occurs

A statistics message will also appear in the terminal (e.g., total motifs found):
```
[Info] Found X motif(s) of Y subgraph(s).
```


## Notes
- If `bf` is not in the current directory, use its absolute path (e.g., `/home/user/tools/bf`).
- Enclose paths with spaces in quotes (e.g., `./bf 3 "my taxon.csv" < "data/file.csv"`).
- Larger K values may increase runtime significantly; use reasonable values (e.g., K≤5) based on data size.


# Random Subgraph Motif Analysis Tool - Usage Instructions

## Overview
This tool identifies subgraph motifs of a specified size (K) from network data through random sampling and counts their occurrences. The output includes the subgraph's classification information (taxonID), structure, and the number of times it was sampled.


## Command Format
```bash
./random <K-value> <number_of_samples> <taxon_file_path> < <data_file_path>
```


## Parameter Explanation
| Parameter Position       | Description                          | Example Value (matching the actual command) |
|--------------------------|--------------------------------------|---------------------------------------------|
| First parameter          | Subgraph size (K, positive integer)  | `3` (analyzes 3-node subgraphs)             |
| Second parameter         | Number of random samples (R, positive integer) | `1000000` (performs 1,000,000 random samplings) |
| Third parameter          | Path to the taxon file               | `TaxonID.csv` (taxon file in the current directory) |
| Input redirection part   | Path to the network data file        | `data/M0275/M0275M_Birth.species_species.csv` |


## Practical Run Example
Based on the command you provided, the complete execution method is as follows:
```bash
./random 3 1000000 MC_TaxonID.csv < data/M0275/M0275M_Birth.species_species.csv
```
- This command will analyze **3-node subgraphs** through **1,000,000 random samples**, extract subgraph motifs from the data file `data/M0275/M0275M_Birth.species_species.csv`, and output results combined with classification information from `TaxonID.csv`.


## Input File Requirements
1. **Taxon File**:  
   CSV format containing mappings between node reference IDs and taxonIDs (parsing logic is in the `read_taxon` function of the code).

2. **Data File**:  
   CSV format where the first line lists node identifiers, and subsequent lines describe the connectivity between the corresponding node and other nodes (used to build the adjacency matrix; parsing logic is in the `read_data` function of the code).


## Output Description
Each line outputs a subgraph motif in the following format:
```
K  taxonID1  taxonID2  ...  taxonIDK  e11 e12 ... eKK  sample_count
```
- `taxonID1...taxonIDK`: Taxon IDs of each node in the subgraph
- `e11...eKK`: Adjacency matrix of the subgraph (1 indicates an edge exists, 0 indicates no edge)
- The last value: The number of times this motif was found in random sampling

A statistical message will also be displayed in the terminal, for example:
```
[Info] Found X motif(s) of Y subgraph(s).
```
(Indicating a total of X motifs found, corresponding to Y sampled subgraphs)


## Notes
- If the `random` program is not in the current directory, use an absolute path (e.g., `/home/user/tools/random`).
- If paths contain spaces, enclose them in quotes (e.g., `./random 3 1000000 "taxon file.csv" < "data file.csv"`).
- A larger number of samples (R-value) results in more accurate distribution estimates but longer runtime; adjust based on data size.
