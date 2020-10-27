package com.codeforces;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class WayTooLongWords {

    public static void main(String[] args) throws IOException {

        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(reader.readLine());

        for (int i = 0; i < n; ++i) {

            String string = reader.readLine();

            if (string.length() <= 10) {

                System.out.println(string);

            } else {

                StringBuilder result = new StringBuilder();

                result
                    .append(string.charAt(0))
                    .append(string.length() - 2)
                    .append(string.charAt(string.length() - 1));

                System.out.println(result.toString());

            }
        }

    }
}
