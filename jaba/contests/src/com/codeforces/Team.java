package com.codeforces;

import java.util.Scanner;

public class Team {

    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int result = 0;
        for (int i = 0; i < n; ++i) {

            int votes = 0;
            for (int j = 0; j < 3; ++j) {
                int t = in.nextInt();
                if (t == 1) {
                    ++votes;
                }
            }
            if (votes > 1) {
                ++result;
            }
        }
        in.close();
        System.out.println(result);
    }
}
