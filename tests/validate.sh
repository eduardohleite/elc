#!/bin/bash

. osht.sh

PLAN 10

run_script() {
    local SCRIPT=$1
    OUTPUT=$(cat ./$SCRIPT | ../out/release/elc)
}

# valuetypevars.e
run_script "valuetypevars.e"
IS "$OUTPUT" == *"30 (type: Integer)"

# condition.e
run_script "condition.e"
IS "$OUTPUT" == *"10 (type: Integer)"

# loops.e
run_script "loops.e"
IS "$OUTPUT" == *"5050 (type: Integer)"

# vector.e
run_script "vector.e"
IS "$OUTPUT" == *"Vector with 4 elements"*
IS "$OUTPUT" == *"0 (type: Integer)"*
IS "$OUTPUT" == *"10 (type: Integer)"*
IS "$OUTPUT" == *"false (type: Boolean)"*

# func.e
run_script "func.e"
IS "$OUTPUT" == *"5 (type: Integer)"

# scope.e
run_script "scope.e"
IS "$OUTPUT" == *"20 (type: Integer)"

# fibonacci.e
run_script "fibonacci.e"
IS "$OUTPUT" == *"6765 (type: Integer)"