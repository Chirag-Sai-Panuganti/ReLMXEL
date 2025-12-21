# DRAMSys Simulator
**DRAMSys** is a flexible DRAM subsystem design space exploration framework based on SystemC TLM-2.0. It was developed by the Microelectronic Systems Design Research Group at RPTU Kaiserslautern-Landau, by Fraunhofer IESE and by the Computer Engineering Group at JMU Würzburg.

## Dependencies
### Compiler and Build Tools
- **C++17 Compiler**: DRAMSys requires a C++17 compatible compiler.
- **CMake**: Minimum version 3.24 is required for the build process.

### SystemC
- DRAMSys is based on **SystemC**. SystemC is included with FetchContent and will be built automatically with the project.
- If you prefer to use a preinstalled version of SystemC, export the environment variable `SYSTEMC_HOME` (the SystemC installation directory) and enable the `DRAMSYS_USE_EXTERNAL_SYSTEMC` CMake option.
- Make sure that the preinstalled SystemC library is built with the same C++ version as the one you are using for DRAMSys.


## Setting up DRAMSys
### Steps:
1. Replace the files `Controller.h` and `Controller.cpp` in `DRAMSys/src/libdramsys/DRAMSys/controller` with the corresponding files in the **Modifications** directory for extracting additonal performance metrics.

2. Replace the files `StlPlayer.h` and `StlPlayer.cpp` in `DRAMSys/src/simulator/simulator/player` with the corresponding files in the **Modifications** directory for splitting the trace at regular intervals.

3. Build the simulator: 
```console
$ cd DRAMSys
$ cmake -B build -D DRAMSYS_WITH_DRAMPOWER=Y
$ cmake --build build
```

4. Change the `PowerAnalysis` parameter from .json files in `DRAMSys/configs/simconfig/` to **true**

5. Verify the working of simulator by: 
```console
$ ./DRAMSys/build/bin/DRAMSys ./configs/ddr4-example.json
```

6.	Add the `fr_fcfs_test.json` in `DRAMSys/configs/mcconfig/` from the **Modifications** directory.


## Simulating
### Steps:
1.	When running the Baseline.py, the baseline configuration at `$ ./DRAMSys/configs/mcconfig/fr_fcfs.json` for **DRAMSys** memory controller parameters is set as follows:

```json
{
    "mcconfig": {
        "PagePolicy": "OpenAdaptive",
        "Scheduler": "FrFcfs",
        "SchedulerBuffer": "Bankwise",
        "RequestBufferSize": 8,
        "CmdMux": "Oldest",
        "RespQueue": "Reorder",
        "RefreshPolicy": "AllBank",
        "RefreshMaxPostponed": 8,
        "RefreshMaxPulledin": 8,
        "PowerDownPolicy": "NoPowerDown",
        "Arbiter": "Reorder",
        "MaxActiveTransactions": 128,
        "RefreshManagement": false
    }
}
```

2.	Change the `mcconfig` parameter to `fr_fcfs.json` in `$ ./DRAMSys/configs/ddr4-example.json` when running Baseline.py and `fr_fcfs_test.json` when running ReLMXEL.py.

3.	Change the `name` parameter to `trace_name.stl` in `$ ./DRAMSys/configs/ddr4-example.json`.


## References
L. Steiner, M. Jung, F. S. Prado, K. Bykov, N. Wehn. International Conference on Embedded Computer Systems: Architectures, Modeling, and Simulation (SAMOS), July, 2020, Samos Island, Greece.
