using Google.FlatBuffers;

namespace OptiKlavi.UI;
 
public unsafe class UnsafeByteBufferAllocator : ByteBufferAllocator
{
    private readonly byte* _bufferPtr;
    private readonly int _bufferSize;

    public UnsafeByteBufferAllocator(byte* externalBuffer, int size)
    {
        _bufferPtr = externalBuffer;
        _bufferSize = size;
        Length = size;
    }
    
    public override Span<byte> Span => new Span<byte>(_bufferPtr, _bufferSize);
    public override ReadOnlySpan<byte> ReadOnlySpan => new ReadOnlySpan<byte>(_bufferPtr, _bufferSize);
    public override Memory<byte> Memory => new Memory<byte>(Span.ToArray());
    public override ReadOnlyMemory<byte> ReadOnlyMemory => new ReadOnlyMemory<byte>(ReadOnlySpan.ToArray());
    
    public override void GrowFront(int newSize)
    {
        throw new NotSupportedException("GrowFront is not supported in deserialization mode.");
    }
}
