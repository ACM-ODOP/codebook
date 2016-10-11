// https://blog.kuoe0.tw/posts/2012/01/28/bitwise-operation-set-operation/

// 列舉集合 S 的所有子集合
int temp = S;
do {
    // proccess
    temp = (temp - 1) & S;
} while (temp != S);

// 列舉有 n 個元素的宇集合 U 中所有大小為 k 的子集合
int temp = (1 << k) - 1;
while (temp < (1 << n)) {
    // proccess
    int last_1 = temp & -temp;
    int carry = temp + last_1;
    int cont_bits = temp & (~carry);
    int trail = (cont_bit / last_1) >> 1;
    temp = carry | trail;
}
