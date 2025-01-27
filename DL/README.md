

The lab manual seems to be largely following [this](https://pytorch.org/tutorials/beginner/introyt/introyt_index.html).

Use `%%time` and `%%timeit`. 

**Moving to the GPU**
```python
if torch.accelerator.is_available():
    tensor = tensor.to(torch.accelerator.current_accelerator())

# OR

device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else "cpu"
print(f"Using {device} device")
```

