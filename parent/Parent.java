package parent;

import com.google.devtools.build.runfiles.Runfiles;

import java.io.IOException;
import java.util.stream.Collectors;

public class Parent {
    public static void main(String[] args) throws IOException {
        Runfiles runfiles = Runfiles.create();
        String childPath = runfiles.rlocation("__main__/child/child");
        System.out.printf("Runfiles variables in parent:%n%s%n",
                runfiles.getEnvVars().entrySet().stream()
                        .map(e -> String.format("%s=%s", e.getKey(), e.getValue()))
                        .collect(Collectors.joining("\n")));
        System.out.printf("Starting child: %s%n%n", childPath);
        ProcessBuilder childProcess = new ProcessBuilder();
        childProcess.command(childPath);
        childProcess.environment().putAll(runfiles.getEnvVars());
        childProcess.inheritIO();
        childProcess.start();
    }
}
