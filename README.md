# GUser-SIRIUS-v1
SIRIUS (Spectroscopy and Identification of Rare Isotopes Using S3) is a charged particle and gamma-ray detection array which will be installed at the focal plane of S3 to perform decay spectroscopic studies in the region of very heavy and superheavy nuclei. When it be complete, it will be capable of detecting heavy ions and their subsequent decays products: alpha particles, internal conversion electrons, gamma rays, X-rays, beta particles and fission products. It is composed of a SeD (Secondary electron Detector) to track the ions and measure their times of flight, a DSSD (double-sided silicon strip detector) for implanting the ions and establish position and time correlations with their successive decays, a tunnel detector, placed upstream to the DSSD, which consists of 4 stripy pad silicon detectors to detect the ionizing particles that escape the DSSD, five Germanium detectors placed in a close geometry around the silicon detectors for gamma spectroscopy. SIRIUS is in the comissioning phase now at GANIL. This softwre is used to treat the data from GANIL's acquisition system. At the core of this software is the GUser class (details can be found here https://gitlab.in2p3.fr/Ganil-acq/Analysis/gru/-/tree/master/UserCode/GUser). This project uses GRU and MFM libraries developed by Luc Legeard (legeard@ganil.fr) to read data. This project shows how one can integrate user libraries into the GUser class.



Install:
To install this software you must have GRU and MFM installed in your system. The links are given below: GRU https://gitlab.in2p3.fr/Ganil-acq/Analysis/gru MFM https://gitlab.in2p3.fr/Ganil-acq/Analysis/MFMlib

This version of the GUser-SIRIUS project shows how to setup the Makefile and CMakeList.txt file in order to integrate user defined classes into the GUser class.

There are two options to build this project:
1. using GNU make
make


2. using CMake
mkdir build
cd build 
cmake ../GUser-SIRIUS
make

Note: This version is not maintained very often. Please consult the other version (https://github.com/RikelC/GUser-SIRIUS).

