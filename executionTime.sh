CONTAINER_ID='day03' #The docker container id
  
START=$(docker inspect --format='{{.State.StartedAt}}' $CONTAINER_ID)
STOP=$(docker inspect --format='{{.State.FinishedAt}}' $CONTAINER_ID)

START_TIMESTAMP=$(date --date=$START +%s%N)
STOP_TIMESTAMP=$(date --date=$STOP +%s%N)

echo "START" $START_TIMESTAMP
echo "STOP " $STOP_TIMESTAMP
echo


MEASURED_TIME=$((($STOP_TIMESTAMP-$START_TIMESTAMP)/1000000))
if [ "$MEASURED_TIME" -lt 0 ]; then
    echo 0
else
    echo "Millisecond" $MEASURED_TIME
fi

MEASURED_TIME=$((($STOP_TIMESTAMP-$START_TIMESTAMP)/1000))
if [ "$MEASURED_TIME" -lt 0 ]; then
    echo 0
else
    echo "Microsecond" $MEASURED_TIME
fi

MEASURED_TIME=$((($STOP_TIMESTAMP-$START_TIMESTAMP)))
if [ "$MEASURED_TIME" -lt 0 ]; then
    echo 0
else
    echo "Nanosecond " $MEASURED_TIME
fi