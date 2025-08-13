import java.util.*;

class PasswordCracker {
    static int MAX_PASSWORD = 9999;

    public static void main(String[] args) {
        var rand = new Random();
        var vault = new Vault(rand.nextInt(MAX_PASSWORD));

        var threads = new ArrayList<Thread>();
        threads.add(new PlusHacker(vault));
        threads.add(new MinusHacker(vault));
        threads.add(new Police());
        for (var thread: threads) {
            thread.start();
        }
    }

    static class Vault {
        int password;

        Vault(int password) {
            this.password = password;
        }

        boolean isCorrectPassword(int password) {
            try {
                Thread.sleep(5);
            } catch (Exception e) {
            }
            return this.password == password;
        }
    }

    abstract static class HackerThread extends Thread {
        Vault vault;

        HackerThread(Vault vault) {
            this.vault = vault;
            this.setName(this.getClass().getSimpleName());
            this.setPriority(Thread.MAX_PRIORITY);
        }

        @Override
        public void start() {
            System.out.println("Starting thread " + this.getName());
            super.start();
        }
    }

    static class PlusHacker extends HackerThread {
        PlusHacker(Vault vault) {
            super(vault);
        }

        @Override
        public void run() {
            for (int guess = 0; guess < MAX_PASSWORD; guess++) {
                System.out.println("Hacker Guessed Password: " + guess);
                if (vault.isCorrectPassword(guess)) {
                    System.out.println(this.getName() + " guessed the password " + guess);
                    System.exit(0);
                }
            }
        }
    }


    static class MinusHacker extends HackerThread {
        MinusHacker(Vault vault) {
            super(vault);
        }

        @Override
        public void run() {
            for (int guess = MAX_PASSWORD; guess >= 0; guess--) {
                System.out.println("Hacker Guessed Password: " + guess);
                if (vault.isCorrectPassword(guess)) {
                    System.out.println(this.getName() + " guessed the password " + guess);
                    System.exit(0);
                }
            }
        }
    }

    static class Police extends Thread {
        @Override
        public void run() {
            for (int i = 10; i > 0; i--) {
                try {
                    Thread.sleep(1000);
                } catch (Exception e) {
                }
                System.out.println("Police: " + i);
            }
            System.out.println("Game over for you hackers");
            System.exit(0);
        }
    }

