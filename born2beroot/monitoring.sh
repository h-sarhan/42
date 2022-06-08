USED_STORAGE=$(df | tail -n +2 | awk '{print $3}' | xargs printf "%d + ")
USED_STORAGE_LEN=$(($(echo $USED_STORAGE | wc -c) - 2))
USED_STORAGE=$(echo $USED_STORAGE | cut -b -$USED_STORAGE_LEN | bc)
USED_STORAGE=$(echo "$USED_STORAGE * 1024" | bc | numfmt --to=si)

TOTAL_STORAGE=$(df | tail -n +2 | awk '{print $2}' | xargs printf "%d + ")
TOTAL_STORAGE_LEN=$(($(echo $TOTAL_STORAGE | wc -c) - 2))
TOTAL_STORAGE=$(echo $TOTAL_STORAGE | cut -b -$TOTAL_STORAGE_LEN | bc)
TOTAL_STORAGE=$(echo "$TOTAL_STORAGE * 1024" | bc | numfmt --to=si)

STORAGE_PCT=$(echo "scale=4; ($USED_STORAGE / $TOTAL_STORAGE) * 100" | bc)

VCPUS=$(lscpu | grep ^CPU\(s\): | grep -Eo '[0-9]+')
CPUS=$(lscpu | grep Socket\(s\): | grep -Eo '[0-9]+')

TOTAL_MEM=$(cat /proc/meminfo | grep MemTotal | grep -Eo '[0-9]+')
TOTAL_MEM_BYTES=$(echo "$TOTAL_MEM * 1024" | bc)

FREE_MEM=$(cat /proc/meminfo | grep MemFree | grep -Eo '[0-9]+')
FREE_MEM_BYTES=$(echo "$FREE_MEM * 1024" | bc)
USED_MEM_BYTES=$(echo "$TOTAL_MEM_BYTES - $FREE_MEM_BYTES" | bc)

MEM_PCT=$(echo "scale=4; ($USED_MEM_BYTES / $TOTAL_MEM_BYTES) * 100" | bc)

CPU_USAGE=$(top -n 1 | grep "%Cpu(s)" | awk '{print $2}')

REBOOT=$(last reboot --time-format iso | head -n 1 | awk '{print $5}' | date +"%Y-%m-%d %H:%M")

LVM=$(cat /etc/fstab | grep "/dev/mapper/*")

TCP=$(ss -s | head -n 2 | grep TCP | awk '{print $4}' | grep -Eo '[0-9]+')

NUM_USERS=$(who | wc -l)

IP_ADDRESS=$(ip a | grep -E '[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+' | awk '{print $2}' | cut -d '/' -f  1 | grep -v '127.0.0.1' | head -n 1)

MAC_ADDRESS=$(ip a | grep ether | awk '{print $2}')

NUM_SUDO=$(journalctl --quiet | cat | grep sudo | grep COMMAND | wc -l)

MESSAGE=$(echo -n "\t#Architecture:" "$(uname -a)\n")
MESSAGE=$(echo -n "${MESSAGE}\t#CPU physical: " $CPUS "\n")
MESSAGE=$(echo -n "${MESSAGE}\t#VCPU: " $VCPUS "\n")

MESSAGE=$(echo -n "${MESSAGE}\t#Memory Usage: " "$(numfmt --to=si $USED_MEM_BYTES)/$(numfmt --to=si $TOTAL_MEM_BYTES)")
MESSAGE=$(echo -n "${MESSAGE} ($(printf "%.2f"  $MEM_PCT)%)\n")
MESSAGE=$(echo -n "${MESSAGE}\t#Disk Usage: " "$USED_STORAGE/$TOTAL_STORAGE" "($(printf "%.2f" $STORAGE_PCT)%)\n")
MESSAGE=$(echo -n "${MESSAGE}\t#CPU load: " "$CPU_USAGE%\n")
MESSAGE=$(echo -n "${MESSAGE}\t#Last boot: " "$REBOOT\n")

MESSAGE=$(echo -n "${MESSAGE}\t#LVM use: ")
if [  "$LVM" ]
then
	MESSAGE=$(echo -n "${MESSAGE}yes\n")
else
	MESSAGE=$(echo -n "${MESSAGE}no\n")
fi
MESSAGE=$(echo -n "${MESSAGE}\t#Connections TCP: " $TCP "ESTABLISHED\n")

MESSAGE=$(echo -n "${MESSAGE}\t#User log:" "$NUM_USERS\n")
MESSAGE=$(echo -n "${MESSAGE}\t#Network: " "IP" $IP_ADDRESS "($MAC_ADDRESS)\n")

MESSAGE=$(echo -n "${MESSAGE}\t#Sudo : " $NUM_SUDO "cmd")
echo -e "$MESSAGE" | wall
