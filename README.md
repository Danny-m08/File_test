# File_test
Tests file types returning program code in unix variable $?




-N EXPRESSION -- Negate EXPRESSION (true->false, false->true)
-d FILE       -- FILE exists and is a directory
-e FILE       -- FILE exists
-f FILE       -- FILE exists and is a regular file
-r FILE       -- FILE exists and read permission is granted
-w FILE       -- FILE exists and write permission is granted
-x FILE       -- FILE exists and execute permission is granted
FILE1 -n FILE2-- FILE1 is newer (modification date) than FILE2
-z VALUE      -- VALUE is “0” or an empty string
EXPRESSION1 EXPRESSION2 EXPRESSION1 and EXPRESSION2 are tested


When multiple conditions are given as shown in the last row of the table above then all must succeed,
for example:
              ./cstest -f somefile -r somefile -w somefile
              
              
Note that -N is an option that takes no option argument. This option indicates that the next EXPRESSION’s logic is
inverted, for example:
                        ./cstest -f somefile -N -r somefile -N -w somefile -x somefile

This example tests if somefile is a file that executable but is not readable and not writeable. Note that -N applies to
a single condition.              
