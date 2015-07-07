# Graphics Assignment
According to university curriculum, Course no **CSE 374** is  **Computer Graphics Lab**. This assignment is a part of that
course and it includes basic operations of Computer
Graphics which are listed below. The `PDF` file named ``Assignment.pdf`` has a little more description about
the work.
  
  1. Line Drawing: Bressenham’s Algorithm
  2. Region Filling: Scanline Algorithm
  3. Transformation (2D): Translation, Rotation, Scaling
  4. Line Clipping: Cohen-Sutherland or Liang-Barsky Algorithm
  5. Projection: Perspective projection of a cube.
  6. A simple Animation like moving any object or transforming one object into another.

Every task has the test cases in comment below the code.

# Compiler Setting

Install **Code::Blocks** on your pc. There is a folder named **GL Files**. In this folder there are three subfolders 
named **include**, **lib** and **dll**. Copy files in **include** folder to the compiler's **include** folder, 
which can be like `C:\Program Files (x86)\CodeBlocks\MinGW\include`. Similarly Copy files in **lib** and files in **dll**
to the compiler's folder named **lib** and **bin** respectively.

Then open the **Code::Blocks** and go to `Setting > Compiler... > Global compiler settings > Linker Setting` and copy
the following lines to the **Other linker options** field:

```
-lbgi
-lgdi32
-lcomdlg32
-luuid
-loleaut32
-lole32
```

Now, it is ready to compile and Run!
