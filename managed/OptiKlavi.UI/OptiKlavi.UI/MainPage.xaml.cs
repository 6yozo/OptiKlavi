using System.Runtime.InteropServices;
using Google.FlatBuffers;

namespace OptiKlavi.UI;

public sealed partial class MainPage : Page
{
    [StructLayout(LayoutKind.Sequential)]
    public struct FlatBufferResult
    {
        public IntPtr buffer;          // Pointer to the unmanaged buffer
        public IntPtr builderContext;  // Pointer to the FlatBufferBuilder
        public int bufferSize;         // Size of the buffer
    }

    [DllImport("OptiKlavi.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern int CalculateNGramFrequency(string filename, ref FlatBufferResult result);

    [DllImport("OptiKlavi.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern void FreeResult(ref FlatBufferResult result);
    
    public MainPage()
    {
        this.InitializeComponent();
    }

    public static Dictionary<string, int> DeserializeFrequencyMap(byte[] buffer)
    {
        // Create a ByteBuffer from the byte array
        var byteBuffer = new ByteBuffer(buffer);

        // Get the root of the FlatBuffer (FrequencyMap)
        var frequencyMap = FrequencyMap.FrequencyMap.GetRootAsFrequencyMap(byteBuffer);

        // Create a dictionary to hold the deserialized key-value pairs
        var frequencyDict = new Dictionary<string, int>();

        // Loop through all the entries in the FlatBuffer
        for (int i = 0; i < frequencyMap.EntriesLength; i++)
        {
            var entry = frequencyMap.Entries(i);
            if (entry == null)
            {
                throw new InvalidOperationException($"Null entry found at index {i}. This is considered an error.");
            }

            var key = entry.Value.Key ??
                      throw new InvalidOperationException($"Null Key found at index {i}. This is considered an error.");
            var value = entry.Value.Value;
                
            frequencyDict[key] = value;
        }

        return frequencyDict;
    }
    
    private void Button_Click(object sender, RoutedEventArgs e)
    {
        CalculateNGramFrequencyCommand();
    }

    private unsafe void CalculateNGramFrequencyCommand()
    {
        FlatBufferResult result = new FlatBufferResult();
        
        string corporaFile = "../../corpora/hun_wikipedia_2021_300K/hun_wikipedia_2021_300K-sentences.txt";
        int status = CalculateNGramFrequency(corporaFile, ref result);
        if ( status != 0 || result.bufferSize == 0 || result.buffer == IntPtr.Zero)
        {
            throw new InvalidOperationException("Failed to calculate NGram Frequency!");
        }
        
        ByteBufferAllocator allocator =
            new UnsafeByteBufferAllocator((byte*)result.buffer.ToPointer(), result.bufferSize);
        ByteBuffer byteBuffer = new ByteBuffer(allocator, 0);
        var frequencyMap = FrequencyMap.FrequencyMap.GetRootAsFrequencyMap(byteBuffer);

        using (StreamWriter writer = new StreamWriter("output2.txt"))
        {
            writer.WriteLine("Entries length: " + frequencyMap.EntriesLength);
            for (int i = 0; i < frequencyMap.EntriesLength; i++)
            {
                var entry = frequencyMap.Entries(i);
                char key = entry.Value.Key[0];
                writer.WriteLine($"{entry?.Key} - Frequency: {entry?.Value}");
            }
        }        
        // Free the FlatBufferBuilder after use
        FreeResult(ref result);
    }
}

