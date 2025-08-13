import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.*;

public class Recolor {
    public static void main(String[] args) throws IOException {
        var recolor = new Recolor();
        String help_message = "Help:\n"+ "  " +
            recolor.getClass().getName() + " <input_filename> <output_filename> <threads_number>";
        String filename = "";
        String outputFilename = "output_img.png";
        int threads = 0;

        if (args.length < 1) {
            System.out.println("Error: no argumets are provided.");
            System.out.println(help_message);
            System.exit(1);
        }
        for (int i = 0; i < args.length; i++) {
            if (i == 0) {
                if (args[0].equals("--help")) {
                    System.out.println(help_message);
                    System.exit(0);
                }
                filename = args[0];
            } else if (i == 1) {
                outputFilename = args[1];
            } else if (i == 2) {
                threads = Integer.parseInt(args[2]);
            } else {
                System.out.println("Error: too many arguments are provided: " + Arrays.toString(args));
                System.out.println(help_message);
                System.exit(1);
            }
        }

        BufferedImage ogImage = ImageIO.read(new File(filename));
        BufferedImage outImage = new BufferedImage(
            ogImage.getWidth(), ogImage.getHeight(), BufferedImage.TYPE_INT_RGB
        );

        if (threads == 0) {
            recolor.recolorSingleThread(ogImage, outImage);
        } else {
            recolor.recolorMultiThread(ogImage, outImage, threads);
        }

        String extension = outputFilename.substring(outputFilename.lastIndexOf('.') + 1);
        ImageIO.write(outImage, extension, new File(outputFilename));
    }

    public void recolorSingleThread(BufferedImage ogImage, BufferedImage outImage) {
        recolorImage(ogImage, outImage, 0, 0, ogImage.getWidth(), ogImage.getHeight());
    }

    public void recolorMultiThread(
            BufferedImage ogImage, BufferedImage outImage, int threads_num
    ) {
        List<Thread> threads = new ArrayList<>();
        int width = ogImage.getWidth();
        int height = ogImage.getHeight() / threads_num;

        for (int i = 0; i < threads_num; i++) {
            final int threadMultiplier = i;

            Thread thread = new Thread(() -> {
                int xOrigin = 0;
                int yOrigin = height * threadMultiplier;

                recolorImage(ogImage, outImage, xOrigin, yOrigin, width, height);
            });
            threads.add(thread);
        }

        for (Thread thread: threads) {
            thread.start();
        }
        for (Thread thread: threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
            }
        }
    }

    public void recolorImage(
        BufferedImage ogImage, BufferedImage outImage,
        int leftCorner, int topCorner, int width, int height
    ) {
        for(int x = leftCorner ; x < leftCorner + width && x < ogImage.getWidth() ; x++) {
            for(int y = topCorner ; y < topCorner + height && y < ogImage.getHeight() ; y++) {
                int rgb = ogImage.getRGB(x, y);

                int red = getRed(rgb);
                int green = getGreen(rgb);
                int blue = getBlue(rgb);

                int newRed;
                int newGreen;
                int newBlue;

                if (isShadeOfGray(red, green, blue)) {
                    newRed = Math.min(255, red + 10);
                    newGreen = Math.max(0, green - 80);
                    newBlue = Math.max(0, blue - 20);
                } else {
                    newRed = red;
                    newGreen = green;
                    newBlue = blue;
                }
                int newRGB = createRGBFromColors(newRed, newGreen, newBlue);
                outImage.getRaster().setDataElements(
                    x, y,
                    outImage.getColorModel().getDataElements(newRGB, null)
                );
            }
        }
    }

    public boolean isShadeOfGray(int red, int green, int blue) {
        return Math.abs(red - green) < 30
            && Math.abs(red - blue) < 30
            && Math.abs(green - blue) < 30;
    }

    public int createRGBFromColors(int red, int green, int blue) {
        int rgb = 0;
        rgb |= blue;
        rgb |= green << 8;
        rgb |= red << 16;
        rgb |= 0xFF000000;
        return rgb;
    }

    public int getRed(int rgb) {
        return (rgb & 0x00FF0000) >> 16;
    }
    public int getGreen(int rgb) {
        return (rgb & 0x0000FF00) >> 8;
    }
    public int getBlue(int rgb) {
        return rgb & 0x000000FF;
    }
}
