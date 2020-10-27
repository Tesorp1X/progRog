package com.codeforces;



import java.util.Scanner;

public class KefaAndFirstSteps {
    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int [] array = new int[n];
        for (int i = 0; i < n; ++i) {
            array[i] = in.nextInt();
        }
        in.close();

        int max_length = 1;
        int current_length = 1;
        for (int i = 1; i < n; ++i) {
            if (array[i - 1] <= array[i]) {
                ++current_length;
            } else if (current_length > max_length) {
                max_length = current_length;
                current_length = 1;
            } else {
                current_length = 1;
            }
        }
        if (current_length > max_length) {
            max_length = current_length;
        }

        System.out.println(max_length);
    }
}
