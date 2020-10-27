package com.codeforces;

import java.util.Scanner;

public class Football {


    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        String string = in.nextLine();
        if (string.length() < 8) {
            System.out.println("NO");
            return;
        }

        char last_char = string.charAt(0);
        int sequence_length = 1;
        for (int i = 1; i < string.length(); ++i) {
            if (sequence_length >= 7) {
                System.out.println("YES");
                return;
            }
            char ch = string.charAt(i);
            if (ch == last_char) {
                ++sequence_length;
            } else {
                last_char = ch;
                sequence_length = 1;
            }
        }

        if (sequence_length >= 7) {
            System.out.println("YES");
            return;
        } else {
            System.out.println("NO");
        }
        /*if (string.contains("0000000") || string.contains("1111111")) {
            System.out.println("YES");
        } else {
            System.out.println("NO");
        }*/
    }
}
