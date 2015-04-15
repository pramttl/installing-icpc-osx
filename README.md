Installing Intel ICPC on OS X Yosemite for using OpenMP
-------------------------------------------------------


1. Download Intel® Parallel Studio XE Composer Edition for C++ OS X.
   It is free for university students.

   https://software.intel.com/en-us/intel-parallel-studio-xe/try-buy

2. I am a student so I applied for a student license. I got an email with the serial key and a download link.
   There were multiple download options. I used the online installer option which is a 13 MB .dmg package which
   will when run will fetch the Intel Parallel Studio XE Composer and install.

3. Download and run that package. It will install and bundle OpenMP with Xcode.


4. Here is a simple OpemMP program that sets the number of threads to use equal to the number of cores on the system.

    ``` myprog.c

    #include <stdio.h>
    #include <omp.h>
     
    int main(void)
    {
        // Number of cores available
        int ncores = omp_get_num_procs( );
        omp_set_num_threads(omp_get_num_procs( ));

        #pragma omp parallel default(none)
        {
            printf("Hello, World, from thread #%d ! \n" , omp_get_thread_num( ));
        }
    }
    ```


   I tried to run `icpc -fopenmp myprog.c -o myprog` and to my surprise that threw an error.

   ```
  dyld: Library not loaded: libiomp5.dylib
  Referenced from: /Users/pranjal/osu/parallel-prog-cs575/./hello
  Reason: image not found
  Trace/BPT trap: 5
  ```

5. I tried to search the cause of the error online and it took me a while to figure out how to fix this.
   I had to set this environment variable on my shell using the following command.

   ```export DYLD_LIBRARY_PATH="/opt/intel/composer_xe_2015.2.132/compiler/lib/:$DYLD_LIBRARY_PATH"```

   Note: You will likely have to make a small change to this command depending on the version of the Intel composer you are using.
   Something like:

   ```export DYLD_LIBRARY_PATH="/opt/intel/composer_xe_<your_composer_version>/compiler/lib/:$DYLD_LIBRARY_PATH"```

6. Then I ran `icpc -fopenmp myprog.c -o myprog` and it compiled without errors. I ran `./myprog`. It worked as expected. :)


    ```
    Hello, World, from thread #3 !
    Hello, World, from thread #0 !
    Hello, World, from thread #2 !
    Hello, World, from thread #1 !
    ```

    Ran again:

    ```
    Hello, World, from thread #1 !
    Hello, World, from thread #0 !
    Hello, World, from thread #2 !
    Hello, World, from thread #3 !
    ```

    There is nothing wrong here. Thread order is not deterministic so everytime we run the program there could be a new order of the treads.


My story
--------

I wanted to use OpenMP on Mac OS X for my CS575 Parallel Programming class at Oregon State University. OpenMP requires you to `include <omp.h>` in your files. I tried using `g++ -fopenmp myprog.c -o myprog` and it did not work giving an `omp.h` file missing error.
I saw that OS X g++ does not have omp by default and there was no clear documentation online on how to install it.
Besides my professor had suggested using ICPC because it has better support of OpenMP. So I decided to install Intel Parallel Studio XE,
which ships with icpc.

P.S: If anyone knows how to make OpenMP work with g++ I would be glad if you can send a PR and add it to this documentation.

Cheers!
