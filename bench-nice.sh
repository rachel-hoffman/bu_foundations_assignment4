#!/bin/bash

echo $(date)
echo "starting matrix multiply"

mkdir -p data/bench-nice-$2

half=$(($1 / 2))

for i in $(eval echo {1..${1}})
do
    # Normal priority
    for j in $(eval echo {1..${half}})
    do
        nice -n 0 /usr/bin/time -f "CPU: %P\n" \
        -o data/bench-nice-$2/mm-${i}-cpu.out \
        ./bench $2 $2 $2 0 > data/bench-nice-$2/mm-${i}.out&
    done

    # Low priority
    for j in $(eval echo {1..${half}})
    do
        nice -n 10 /usr/bin/time -f "CPU: %P\n" \
        -o data/bench-nice-$2/mm-${i}-cpu.out \
        ./bench $2 $2 $2 0 > data/bench-nice-$2/mm-${i}.out&
    done
    
    pids[${i}]=$!
    echo $(date)
done

echo "waiting for multiplies"
# wait for all pids
for pid in ${pids[*]}; do
    wait $pid
done
echo $(date)

echo $(ps)

#kill $monitor
