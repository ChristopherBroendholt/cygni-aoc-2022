FROM gcc as BASE
COPY . .
RUN gfortran -static aoc.f90 -o aoc

FROM alpine
COPY --from=BASE aoc .
COPY input.txt .
CMD ["./aoc"]