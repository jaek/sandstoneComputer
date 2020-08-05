# Sandstone Virtual Machine

As described in [this document](http://www.boundvariable.org/um-spec.txt).

| Instruction | Mnemonic| Code | Description |
| ----------- | --- | --- | ----------- |
| Load Immediate |  LDI R X | 1111 / 15 | Loads a 25bit value x into R   |
| Cond. Move | CMV A B C | 0000 / 0 |  The register A receives the value in register B, unless the register C contains 0. |
| Array Index | ARI | 0001 / 1 | The register A receives the value stored at offset in register C in the array identified by B. | 