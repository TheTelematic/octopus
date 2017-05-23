# octopus
My end-of-degree project, a system based on microservices. Running microservers and launch new of them when the system is colapsed.


Notes:
    Be carefull, in the file CMakeLists.txt must be enabled the drivers!

    To launch with VMware Player and vga the drivers are:
      vmxnet3 vga_output

Instructions for use serverUDP:  

    1 - Write the service
    2 - cd serverUDP/
    3 - ../build.sh
    4 - ../clone.sh

    5.1.1 - cd build/
    5.1.2 - ./vmware serverUDP

    5.2.1 - cd build_2/
    5.2.2 - ./vmware serverUDP
