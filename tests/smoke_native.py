import importlib.util
import importlib.machinery
import sys
from pathlib import Path
native = Path(sys.argv[1]).resolve()
loader = importlib.machinery.ExtensionFileLoader('_EffekseerCore', str(native))
spec = importlib.util.spec_from_file_location('_EffekseerCore', native, loader=loader)
module = importlib.util.module_from_spec(spec)
sys.modules['_EffekseerCore'] = module
spec.loader.exec_module(module)
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'src/python/swig'))
import EffekseerCore as efk
assert efk.EffekseerBackendCore.GetDevice() == efk.EffekseerCoreDeviceType_Unknown
manager = efk.EffekseerManagerCore()
assert manager.Initialize(32) is False
manager.BeginUpdate()
manager.EndUpdate()
effect = efk.EffekseerEffectCore()
del effect, manager
efk.EffekseerBackendCore.Terminate()
print('Python native binding smoke passed:', sys.version.split()[0])
