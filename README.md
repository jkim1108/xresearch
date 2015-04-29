
- Author : Jonghoon Kim
- E-mail : john.jonghoon.kim@gmail.com
- Date : 29/Apr/2015

------------------------------------------------------------------------------

HOW TO RUN

1. Build the project using build.sh
2. Run ./main.o PARAM_FILE
3. It will write a kernel matrix file in result/PARAM_FILE(it can be directly
   loaded from python numpy)

------------------------------------------------------------------------------

HOW TO WRITE PARAMETER FILES

Put in the following parameter names and values delimited with colon(:)
   - dataset : string -- main.o will try to find the datafiles in data/dataset
   - kernelType : string -- model to run (PK or CK or VTK)
   - useDT : int -- whether to use the dependency tree structure(1 or 0)
   - lambda1 : float -- penalisation term for the phrasal length
   - lambda2 : float -- penalisation term for the distortion
   - maxLength : int -- maximum phrasal length to consider
   - alpha : int -- paramter for word kernel
   - useMult : int -- whether to take element-wise multiplication for the CK

------------------------------------------------------------------------------

HOW TO ADD NEW DATASETS

1. Add a new directory in data/
2. Generate dependency trees using FANSE parser
3. Add edges/label of dependency tree as other datasetfiles
4. Add word embedding label/vector files
5. If the new datasets have multi lines per document, add the entry 
   in the main.cpp's isDoc set

- The project is suited to binary classification, when dealing with multi-class
- put everything in .pos and write an empty .neg file
