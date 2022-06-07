
STORAGE=$(df | tail -n +2 | awk '{print $3}' | xargs printf "%d + ")
STORAGE_LEN=$(($(echo $STORAGE | wc -c) - 2))
STORAGE=$(echo $STORAGE | cut -b -$STORAGE_LEN | bc | numfmt --to=iec)


CPU=$(top -n 1 | grep "%Cpu(s)" | awk '{print $2}')
REBOOT=$(last reboot)
echo $CPU
echo $STORAGE
