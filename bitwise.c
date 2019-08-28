int x = 3;

// Find if bit 1 is set
if (x & 0x02) {
	
}

// Set bit 3
x = x | 0x08;

// Set bit 24 (left shift)
x = x | (1 << 24)


// Keep track of priorities that are ready

//Solution 1: 120 bytes
int a[30];
a[15] = 1;
a[20] = 0;
a[15] = 0;

//Solution 2: 30 bytes
char a[30]

//Solution 3: 4 bytes
int prio = 0;
prio = prio | (1 << 15);

//Iterate over prio:
for (int i = 0; i < 32; i++) {
	if (prio & (1 << i);) {
		printf("prio %d is ready", i);
	}
}

//Different way to iterate
while (32 times) {
	if (prio & 0x01) {
		printf("stuff");
	}
	prio = prio >> 1;
}
