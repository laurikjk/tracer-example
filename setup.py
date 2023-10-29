import sys
sys.path.append('./build')  # add the build directory to the Python path

import tracer

t = tracer.Tracer()
t.start()

def test_function():
    print("Inside test function!")

test_function()

t.stop()
