package com.company;

import java.util.Scanner;

public class Football {


    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String string = in.nextLine();
        if (string.length() <= 8) {
            System.out.println("NO");
            return;
        }
        int zeros = 0, ones = 0;

        for (int i = 0; i < string.length(); ++i) {
            if (zeros >= 7 || ones >= 7) {
                System.out.println("YES");
                return;
            }

            if (string.charAt(i) == '0') {
                ++zeros;
            } else {
                ++ones;
            }
        }

        if (zeros >= 7 || ones >= 7) {
            System.out.println("YES");
        }
    }
}
