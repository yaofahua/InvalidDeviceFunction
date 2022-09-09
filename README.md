## CUDA Problem: Invalid Device function

When build [caffe windows](https://github.com/BVLC/caffe/tree/windows) with cuda, I meet this problem: 

```
F0907 15:41:09.264920 202420 im2col.cu:61] Check failed: error == cudaSuccess (8 vs. 0)  invalid device function
```

This project helps me to find the solution, hope to help you.

### My PC environment

- Windows 11
- Visual Studio 2013
- CMake 3.18.0
- Ninja 1.11.1
- CUDA 7.5
- NVIDIA GeForce MX250

### Normal build and exec

CMake support CUDA C++ from 3.9, so I make this sample project, to my surprise, it can run with no errors. What's the difference between this sample project and [caffe windows](https://github.com/BVLC/caffe/tree/windows)?

```batch
build.bat
build\main.exe
Last error: 0
Last error: 0
```

0 means exec successfully.

### Error build and exec

`ninja -t commands` prints all commands that to build main.exe. We see about gpu code is `--generate-code=arch=compute_20,code=[compute_20,sm_20]`, use this method when build [caffe windows](https://github.com/BVLC/caffe/tree/windows), the gpu code is `--generate-code=arch=compute_20,code=sm_20`. Is it reason of this problem ?

```batch
C:\Users\hw\Desktop\src\InvalidDeviceFunction\build>ninja -t commands main.exe
C:\PROGRA~2\MICROS~3.0\VC\bin\amd64\cl.exe  /nologo /TP   /DWIN32 /D_WINDOWS /W3 /GR /EHsc /MDd /Zi /Ob0 /Od /RTC1 /showIncludes /FoCMakeFiles\main.dir\main.cc.obj /FdCMakeFiles\main.dir\ /FS -c ..\main.cc
cmd.exe /C "C:\PROGRA~1\NVIDIA~2\CUDA\v7.5\bin\nvcc.exe    -D_WINDOWS -Xcompiler="/W3 /GR /EHsc" -Xcompiler="-MDd -Zi -Ob0 -Od /RTC1" --generate-code=arch=compute_20,code=[compute_20,sm_20] -x cu -c ..\im2col.cu -o CMakeFiles\main.dir\im2col.cu.obj -Xcompiler=-FdCMakeFiles\main.dir\,-FS && C:\PROGRA~1\NVIDIA~2\CUDA\v7.5\bin\nvcc.exe    -D_WINDOWS -Xcompiler="/W3 /GR /EHsc" -Xcompiler="-MDd -Zi -Ob0 -Od /RTC1" --generate-code=arch=compute_20,code=[compute_20,sm_20] -x cu -M ..\im2col.cu -MT CMakeFiles\main.dir\im2col.cu.obj -o CMakeFiles\main.dir\im2col.cu.obj.d"
cmd.exe /C "cd . && "C:\Program Files\CMake\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\main.dir --rc=C:\PROGRA~2\WI3CF2~1\8.1\bin\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\8.1\bin\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~3.0\VC\bin\amd64\link.exe /nologo CMakeFiles\main.dir\main.cc.obj CMakeFiles\main.dir\im2col.cu.obj  /out:main.exe /implib:main.lib /pdb:main.pdb /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console -LIBPATH:C:\PROGRA~1\NVIDIA~2\CUDA\v7.5\lib\x64 cudadevrt.lib  cudart_static.lib  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib && cd ."
```

So I change `--generate-code=arch=compute_20,code=[compute_20,sm_20]` to `--generate-code=arch=compute_20,code=sm_20` and use following commands to build again.

```batch
C:\PROGRA~2\MICROS~3.0\VC\bin\amd64\cl.exe  /nologo /TP   /DWIN32 /D_WINDOWS /W3 /GR /EHsc /MDd /Zi /Ob0 /Od /RTC1 /showIncludes /FoCMakeFiles\main.dir\main.cc.obj /FdCMakeFiles\main.dir\ /FS -c ..\main.cc
cmd.exe /C "C:\PROGRA~1\NVIDIA~2\CUDA\v7.5\bin\nvcc.exe    -D_WINDOWS -Xcompiler="/W3 /GR /EHsc" -Xcompiler="-MDd -Zi -Ob0 -Od /RTC1" --generate-code=arch=compute_20,code=sm_20 -x cu -c ..\im2col.cu -o CMakeFiles\main.dir\im2col.cu.obj -Xcompiler=-FdCMakeFiles\main.dir\,-FS && C:\PROGRA~1\NVIDIA~2\CUDA\v7.5\bin\nvcc.exe    -D_WINDOWS -Xcompiler="/W3 /GR /EHsc" -Xcompiler="-MDd -Zi -Ob0 -Od /RTC1" --generate-code=arch=compute_20,code=sm_20 -x cu -M ..\im2col.cu -MT CMakeFiles\main.dir\im2col.cu.obj -o CMakeFiles\main.dir\im2col.cu.obj.d"
cmd.exe /C "cd . && "C:\Program Files\CMake\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\main.dir --rc=C:\PROGRA~2\WI3CF2~1\8.1\bin\x64\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\8.1\bin\x64\mt.exe --manifests  -- C:\PROGRA~2\MICROS~3.0\VC\bin\amd64\link.exe /nologo CMakeFiles\main.dir\main.cc.obj CMakeFiles\main.dir\im2col.cu.obj  /out:main.exe /implib:main.lib /pdb:main.pdb /version:0.0 /machine:x64 /debug /INCREMENTAL /subsystem:console -LIBPATH:C:\PROGRA~1\NVIDIA~2\CUDA\v7.5\lib\x64 cudadevrt.lib  cudart_static.lib  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib && cd ."
```

And the result is :

```batch
C:\Users\hw\Desktop\src\InvalidDeviceFunction\build>main.exe
Last error: 8
Last error: 8
```

In CUDA 7.5, 8 means `invalid device function`.

### Conclusion
 
So one solution of `invalid device function` is : Change `--generate-code=arch=compute_20,code=sm_20` to `--generate-code=arch=compute_20,code=[compute_20,sm_20]`. For [caffe windows](https://github.com/BVLC/caffe/tree/windows) project, should modify `.\cmake\Cuda.cmake`, 

```cmake
  # Tell NVCC to add binaries for the specified GPUs
  foreach(__arch ${__cuda_arch_bin})
    if(__arch MATCHES "([0-9]+)\\(([0-9]+)\\)")
      # User explicitly specified PTX for the concrete BIN
      # list(APPEND __nvcc_flags -gencode arch=compute_${CMAKE_MATCH_2},code=sm_${CMAKE_MATCH_1})
      list(APPEND __nvcc_flags -gencode arch=compute_${CMAKE_MATCH_2},code=[compute_${CMAKE_MATCH_2},sm_${CMAKE_MATCH_1}])
      list(APPEND __nvcc_archs_readable sm_${CMAKE_MATCH_1})
    else()
      # User didn't explicitly specify PTX for the concrete BIN, we assume PTX=BIN
      # list(APPEND __nvcc_flags -gencode arch=compute_${__arch},code=sm_${__arch})
      list(APPEND __nvcc_flags -gencode arch=compute_${__arch},code=[compute_${__arch},sm_${__arch}])
      list(APPEND __nvcc_archs_readable sm_${__arch})
    endif()
  endforeach()

  # Tell NVCC to add PTX intermediate code for the specified architectures
  foreach(__arch ${__cuda_arch_ptx})
    list(APPEND __nvcc_flags -gencode arch=compute_${__arch},code=compute_${__arch})
    list(APPEND __nvcc_archs_readable compute_${__arch})
  endforeach()
```