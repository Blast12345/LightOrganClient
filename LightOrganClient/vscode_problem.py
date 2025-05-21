from dataclasses import dataclass
from enum import Enum

class VSCodeSeverity(Enum):
    WARNING = "warning"
    ERROR = "warning" # Treat errors as warnings as lint issues should not block the engineer
    INFO = "info"

@dataclass
class VSCodeProblem:
    file: str
    line: int
    column: int
    severity: VSCodeSeverity
    message: str
    code: str

    def toString(self):
        return f"{self.file}:{self.line}:{self.column}: {self.severity.value}: {self.message} [{self.code}]"