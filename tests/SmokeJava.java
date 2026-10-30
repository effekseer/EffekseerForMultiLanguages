import Effekseer.swig.*;
public class SmokeJava {
  public static void main(String[] args) {
    System.load(new java.io.File(args[0]).getAbsolutePath());
    if (EffekseerBackendCore.GetDevice() != EffekseerCoreDeviceType.Unknown) throw new AssertionError();
    EffekseerManagerCore manager = new EffekseerManagerCore();
    if (manager.Initialize(32)) throw new AssertionError();
    manager.BeginUpdate(); manager.EndUpdate();
    EffekseerEffectCore effect = new EffekseerEffectCore();
    effect.delete(); manager.delete(); EffekseerBackendCore.Terminate();
    System.out.println("Java native binding smoke passed");
  }
}
