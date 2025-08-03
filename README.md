# Motif Analysis in Horizontal Gene Transfer Networks (BIBM_Motif.pdf)

## Abstract
Horizontal gene transfer (HGT) facilitates genetic material exchange between non-parental microorganisms, promoting genetic diversity and adaptability. This study introduces a novel motif detection algorithm for microbial HGT networks, combining exhaustive enumeration and stochastic sampling to identify 3- to 5-node motifs. Analysis of mother-infant (MC) and inflammatory bowel disease (IBD) datasets revealed 29 unique motifs, with probiotic genera in peripheral positions, heritable HGT events in MC, and Pantoea as a potential cross-clade transfer vector in IBD {insert\_element\_0\_}.

## Introduction
HGT networks model gene transfer between donors (nodes) and recipients (edges), offering a systems-level view of genetic flow. Unlike global structural analyses (e.g., power-law distributions, modularity), motif analysis focuses on recurrent small subgraphs—enriched in real networks compared to random ones—uncovering specific transfer patterns like mutual exchange triads or hub-spoke structures {insert\_element\_1\_}.

## Methodology

### Motif Detection Algorithm
1. **Subnetwork Enumeration**  
   - For 3- and 4-node motifs: Exhaustive enumeration via neighbor-expansion DFS, adding only neighbors with IDs larger than the smallest node in the current motif {insert\_element\_2\_}.  
   - For 5-node motifs: Degree-weighted random sampling (probability ∝ 15×degree³, parameters from least squares) to prioritize hub-connected subgraphs {insert\_element\_3\_}.  

2. **Duplicate Removal**  
   Subgraphs are sorted by node ID and encoded into a unique Canonical ID (CID) to eliminate duplicates (e.g., 3-node CID: \((ID_A \times N + ID_B) \times N + ID_C\)) {insert\_element\_4\_}.  

3. **Pre-classification & Identification**  
   Motifs are pre-classified by node type (Taxon ID, via NCBI Taxonomy and TaxonKit) {insert\_element\_5\_}. Isomorphism is confirmed by matching node types and edge patterns across all permutations {insert\_element\_6\_}.  

4. **Optimizations**  
   - Unordered flat sets/maps improve cache efficiency, boosting runtime by 2-3x {insert\_element\_7\_}.  
   - 128-bit integer encoding accelerates subgraph comparison by 10-20x {insert\_element\_8\_}.  

### Datasets
- **MC**: Longitudinal samples (gestation to 3 months post-birth) tracking mother-infant HGT dynamics {insert\_element\_9\_}.  
- **IBD**: Cross-sectional samples (UC, CD, healthy controls) to study disease-associated transfer {insert\_element\_10\_}.  

## Results
- **Motif Distribution**: 29 unique motifs, with star structures (e.g., 1113) most prevalent {insert\_element\_11\_}.  
- **MC Dataset**: Probiotics (e.g., Bacteroides) in peripheral positions; heritable motifs and infant-specific HGT (e.g., Clostridium) {insert\_element\_12\_}.  
- **IBD Dataset**: Bacteroides shows increased intergroup transfer in disease; Pantoea (hub in UC motifs) facilitates cross-clade transfer {insert\_element\_13\_}.  

## Conclusion
Motif analysis reveals ecological roles in HGT networks: peripheral probiotics, heritable patterns in early life, and disease-specific transfer vectors like Pantoea {insert\_element\_14\_}.
