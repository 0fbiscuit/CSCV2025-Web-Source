FROM openjdk:17-jdk-slim

RUN useradd -m -s /bin/bash appuser

WORKDIR /app
COPY gateman.jar /app/gateman.jar
COPY newsman.jar /app/newsman.jar
RUN chown root:root /app/gateman.jar /app/newsman.jar
RUN filename="flag-$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | head -c 32)" \
    && echo "CSCV2025{fake_flag_for_testing}" > "$filename" && chmod 744 "$filename"

EXPOSE 8080
USER appuser

CMD sh -c "java -jar gateman.jar & java -jar newsman.jar"