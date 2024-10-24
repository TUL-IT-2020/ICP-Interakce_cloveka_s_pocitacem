In your Visual Studio project directory:
   create dirs: include, lib, bin 

Project - properties - configuration properties - VC++ directories 

   Select in listbox:"ALL CONFIGURATIONS"
 
   Add to project settings - paths:
   VC++ directories -> Executable dirs:    $(ProjectDir)bin;
                    -> Include dirs:       $(ProjectDir)include;
                    -> Library dirs:       $(ProjectDir)lib;

   Project -> Properties -> Debugging -> Environment
       PATH=%PATH%;$(ProjectDir)bin; 
 
   Project -> Properties -> Linker -> Input -> Additional dependencies
       opengl32.lib;glu32.lib;glew32.lib;glfw3dll.lib;

 
 Download current GLFW (compiled for Windows x64: glfw-3.3.8.bin.WIN64.zip) 
 from https://www.glfw.org/download.html   

     Documentation: https://www.glfw.org
     Extract from ZIP:
       From dir: glfw-3.3.8.bin.WIN64\lib-vc2022\
           glfw3.dll into $(ProjectDir)bin
           *.lib     into $(ProjectDir)lib
       From dir glfw-3.3.8.bin.WIN64\include 
           dir GLFW and its content into $(projectDir)include
       
 Download current GLEW (binary for 32&64 bit Windows: glew-2.2.0-win32.zip)
 from https://sourceforge.net/projects/glew/
 
   Documentation: http://glew.sourceforge.net/  
   Extract from ZIP:
       From dir: glew-2.2.0\bin\Release\x64
           glew32.dll into $(ProjectDir)bin
       From dir: glew-2.2.0\lib\Release\x64    
           *.lib     into $(ProjectDir)lib
       From dir: glew-2.2.0\include\
           dir GL and its content into $(projectDir)include
 
 Download current GLM (header only library) from https://glm.g-truc.net ,
 download 'master' branch as ZIP.
 
     Documentation: https://github.com/g-truc/glm/blob/master/manual.md
     Extract from ZIP:
       From dir: glm-master
           dir glm and its content into $(projectDir)include
 